// Same as c2py_a : wraps L with c2py, with its own wrap_pytype<L>. Importing both must fail, since
// the two Python types are distinct and objects of one would not convert in the other.
// Hand-written and not clair-generated : see the note in L.hpp for why.

#include "L.hpp"

namespace c2py {
  template <> constexpr auto tp_name<L> = "c2py_b.L";
}

static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "c2py_b", "Wraps L with c2py, again", -1, nullptr};

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_c2py_b() {

  if (PyType_Ready(&c2py::wrap_pytype<L>) < 0) return NULL;

  PyObject *m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::add_type_object_to_main<L>("L", m)) {
    Py_DECREF(m);
    return NULL;
  }

  return m;
}
