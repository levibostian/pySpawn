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

void write_to_pipe(int file, char *write) {
  FILE *stream;
  stream = fdopen(file, "w");
  fprintf(stream, "%s", write);
  fclose(stream);
}

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
// const char *command;
  char *command;
  char *script;
  char *command_output = "on linux";

  int pipeparent[2];
  int pipechild[2];
  pid_t cpid;
  char *program_run[2];

  if (pipe(pipeparent) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  if (pipe(pipechild) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  // Get args from Python dev user.
  if (!PyArg_ParseTuple(args, "ss", &command, &script))
    return NULL;

  if (cpid == 0) { // Child
    close(pipeparent[WRITE_END]);
    close(pipechild[READ_END]);

    dup2(pipeparent[READ_END], STDIN_FILENO);
    close(pipeparent[READ_END]);

    dup2(STDOUT_FILENO, pipechild[WRITE_END]);
    close(pipechild[WRITE_END]);

    program_run[0] = command;
    program_run[1] = script;
    if (execvp(program_run[0], program_run) < 0) {
        perror("exec");
        exit(EXIT_FAILURE);
    }

    _exit(EXIT_SUCCESS);
  } else { // Parent
    close(STDIN_FILENO);
    close(pipeparent[READ_END]);
    close(pipechild[WRITE_END]);

    dup2(pipechild[READ_END], STDOUT_FILENO);
    close(pipechild[READ_END]);

    write_to_pipe(pipeparent[WRITE_END], command);
    close(pipeparent[WRITE_END]);

    wait(NULL); // Wait for child
  }

  return PyUnicode_FromFormat("%s with python: %s with command %s", command_output, PYTHON_BIN, command);
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
