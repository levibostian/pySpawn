#include <Python.h>

static PyObject *spawn_run(PyObject *self, PyObject *args) {
  const char *command;
  int sts; 

  if (!PyArg_ParseTuple(args, "s", &command)) 
    return NULL;
  sts = system(command);
  return PyLong_FromLong(sts);
}

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
