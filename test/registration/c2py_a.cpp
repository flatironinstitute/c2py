// Wraps L with c2py, like a generated module init would : ready wrap_pytype<L>, expose it, register
// it. Registers nothing else and has no function, so the tests can pick the import order they need.
// Hand-written and not clair-generated : see the note in L.hpp for why.

#include "L.hpp"

namespace c2py {
  template <> constexpr auto tp_name<L> = "c2py_a.L";
}

static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "c2py_a", "Wraps L with c2py", -1, nullptr};

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_c2py_a() {

  if (PyType_Ready(&c2py::wrap_pytype<L>) < 0) return NULL;

  PyObject *m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  // As the generated init does : a failure here fails the import
  if (not c2py::add_type_object_to_main<L>("L", m)) {
    Py_DECREF(m);
    return NULL;
  }

  return m;
}
