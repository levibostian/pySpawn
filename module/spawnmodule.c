#include <Python.h>

static PyObject *spawn_test(PyObject *self, PyObject *args) {
  const char *command;
  int sts; 

  if (!PyArg_ParseTuple(args, "s", &command)) 
    return NULL;
  sts = system(command);
  return Py_BuildValue("i", sts);
}

static PyMethodDef SpawnMethods[] = {
  {"test", spawn_test, METH_VARARGS,
   "This is just a test to make sure it works."},
  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initspawn(void) {
  (void) Py_InitModule("spawn", SpawnMethods);
}

int main(int argc, char *argv[]) {
  Py_SetProgramName(argv[0]);

  Py_Initialize();

  initspawn();

  return 0;
}
