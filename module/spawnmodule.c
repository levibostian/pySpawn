#include <Python.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define WRITE_END 1
#define READ_END 0

#define MAX_INPUT_LINE_LENGTH 1000
#define MAX_OUTPUT_LENGTH 1000

#if PY_MAJOR_VERSION == 3
#define PYTHON_BIN "python3"
#else
#define PYTHON_BIN "python2.7"
#endif

#ifdef _WIN32
static PyObject *spawn_run(PyObject *self, PyObject *args) {
  const char *command;
  char *command_output = "on windows";

  if (!PyArg_ParseTuple(args, "s", &command))
    return NULL;

  return PyUnicode_FromFormat("%s with python: %s", command_output, PYTHON_BIN);
}
#else
static PyObject *spawn_run(PyObject *self, PyObject *args) {
  char *command;
  char *script;
  char *input;

  int pipeparent[2];
  int pipechild[2];
  pid_t cpid;
  char *program_run[2];
  char child_buf[1025];
  memset(child_buf, '\0', sizeof(child_buf));

  char other_child_buf[1025];
  memset(other_child_buf, '\0', sizeof(other_child_buf));

  if (pipe(pipeparent) == -1) {
    perror("pipe 1");
    exit(EXIT_FAILURE);
  }

  if (pipe(pipechild) == -1) {
    perror("pipe 2");
    exit(EXIT_FAILURE);
  }

  // Get args from Python dev user.
  if (!PyArg_ParseTuple(args, "sss", &command, &script, &input))
    return NULL;

  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (cpid == 0) { // Child
    close(pipeparent[WRITE_END]);
    close(pipechild[READ_END]);

    if ((dup2(pipeparent[READ_END], STDIN_FILENO)) == -1) {
      perror("dup2 pipeparent[READ] copy to STDIN error");
      exit(EXIT_FAILURE);
    }
    close(pipeparent[READ_END]);

    if ((dup2(pipechild[WRITE_END], STDOUT_FILENO)) == -1) {
      perror("dup2 pipechild[WRITE] copy to STDOUT error");
      exit(EXIT_FAILURE);
    }
    close(pipechild[WRITE_END]);

    program_run[0] = command;
    program_run[1] = script;
    if (execvp(program_run[0], program_run) < 0) {
        perror("exec error");
        exit(EXIT_FAILURE);
    }

    _exit(EXIT_SUCCESS);
  } else { // Parent
//    close(STDIN_FILENO); // don't close STDIN in parent or Python REPL will exit.
    close(pipeparent[READ_END]);
    close(pipechild[WRITE_END]);

    write(pipeparent[WRITE_END], input, strlen(input));
    close(pipeparent[WRITE_END]);
//    fsync(pipeparent[WRITE_END]);

    int n;
    if ((n = read(pipechild[READ_END], child_buf, 1024)) >= 0) {
      // do something with what got read here. The reading is done.
    }

    if ((n = read(pipechild[READ_END], other_child_buf, 1024)) >= 0) {
          // do something with what got read here. The reading is done.
        }
    close(pipechild[READ_END]);

    wait(NULL); // Wait for child
  }

//close(pipeparent[WRITE_END]);
  return PyUnicode_FromString(other_child_buf);
}
#endif

static PyMethodDef SpawnMethods[] = {
  {"run", spawn_run, METH_VARARGS,
   "Run a command while sending STDIN input and capturing STDOUT."},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef spawnmodule = {
  PyModuleDef_HEAD_INIT,
  "_spawn",
  NULL,
  -1,
  SpawnMethods
};

PyMODINIT_FUNC PyInit__spawn(void) {
  return PyModule_Create(&spawnmodule);
}

int main(int argc, char *argv[]) {
  PyImport_AppendInittab("_spawn", PyInit__spawn);

  Py_SetProgramName(argv[0]);

  Py_Initialize();

  PyImport_ImportModule("_spawn");

  return 0;
}
