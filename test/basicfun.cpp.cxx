
// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#include "c2py/c2py.hpp"

#include "/Users/oparcollet/src/clair/test/c2py/basicfun.cpp"

// ==================== enums =====================

// ==================== module classes =====================

// ==================== module functions ====================

static PyObject *fun_0(PyObject *self, PyObject *args, PyObject *kwargs) {
  static overloads_t ovs = {cfun(pycast<int>(f), "x"), cfun(pycast<int, int>(f), "x", "y")};
  return ovs(self, args, kwargs);
}
static PyObject *fun_1(PyObject *self, PyObject *args, PyObject *kwargs) {
  static overloads_t ovs = {cfun(pycast<int, int>(g), "x", "y"_a = 8)};
  return ovs(self, args, kwargs);
}
static PyObject *fun_2(PyObject *self, PyObject *args, PyObject *kwargs) {
  static overloads_t ovs = {cfun(pycast<>(hello))};
  return ovs(self, args, kwargs);
}

//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"f", (PyCFunction)fun_0, METH_VARARGS | METH_KEYWORDS, "Doc XXX"},
   {"g", (PyCFunction)fun_1, METH_VARARGS | METH_KEYWORDS, "Doc XXX"},
   {"hello", (PyCFunction)fun_2, METH_VARARGS | METH_KEYWORDS, "Doc XXX"},
   {NULL} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "basicfun", /* name of module */
                                        "DOC MODULE",                      /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_basicfun() {

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *cpp2py::conv_table_sptr.get();

  // Initialization of the module
  c2py::modules::basicfun::init();
  return m;
}
