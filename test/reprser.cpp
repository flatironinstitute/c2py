// Low level test of the repr based serialization : hand written module, no code generation.

#ifdef __clang__
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif

#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#include "c2py/c2py.hpp"

#include <iostream>

struct R {
  int k = 0;

  R() = default;
  R(int i) : k(i) {}

  bool operator==(R const &) const = default;
};

// The repr must be valid Python, evaluating back to an equal object in the module R is wrapped in.
std::ostream &operator<<(std::ostream &out, R const &r) { return out << "R(" << r.k << ")"; }

using namespace c2py;

template <> constexpr bool c2py::is_wrapped<R>         = true;
template <> constexpr bool c2py::serialize_via_repr<R> = true;

namespace c2py {
  template <> constexpr auto tp_name<R> = "reprser.R";
}

static int init_R(PyObject *self, PyObject *args, PyObject *kwargs) {
  static dispatcher_c_kw_t ovs = {c_constructor<R>(), c_constructor<R, int>("i")};
  return ovs(self, args, kwargs);
}

template <> constexpr initproc c2py::tp_init<R> = &init_R;

template <>
PyMethodDef c2py::tp_methods<R>[] = {{"__getstate__", c2py::getstate_repr<R>, METH_NOARGS, ""},
                                     {"__setstate__", c2py::setstate_repr<R>, METH_O, ""},
                                     {NULL}};

template <>
constinit PyGetSetDef c2py::tp_getset<R>[] = {{"k", get_member<&R::k, R>, set_member<&R::k, R>, "Doc of k member", nullptr}, //
                                              {NULL}};

// Two more classes, only to exercise the tp_name guards of setstate_repr : one naming a module
// that can not be imported, one with no module qualification at all.
struct BadModule {};
struct NoModule {};

template <> constexpr bool c2py::is_wrapped<BadModule> = true;
template <> constexpr bool c2py::is_wrapped<NoModule>  = true;

namespace c2py {
  template <> constexpr auto tp_name<BadModule> = "no_such_module_xyz.BadModule";
  template <> constexpr auto tp_name<NoModule>  = "NoModule";
} // namespace c2py

template <>
PyMethodDef c2py::tp_methods<BadModule>[] = {{"__setstate__", c2py::setstate_repr<BadModule>, METH_O, ""}, //
                                             {NULL}};

template <>
PyMethodDef c2py::tp_methods<NoModule>[] = {{"__setstate__", c2py::setstate_repr<NoModule>, METH_O, ""}, //
                                            {NULL}};

static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "reprser", "Test of repr based serialization", -1, nullptr};

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_reprser() {

#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  if (PyType_Ready(&wrap_pytype<R>) < 0) return NULL;
  if (PyType_Ready(&wrap_pytype<BadModule>) < 0) return NULL;
  if (PyType_Ready(&wrap_pytype<NoModule>) < 0) return NULL;

  PyObject *m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not add_type_object_to_main<R>("R", m)) return NULL;
  if (not add_type_object_to_main<BadModule>("BadModule", m)) return NULL;
  if (not add_type_object_to_main<NoModule>("NoModule", m)) return NULL;

  return m;
}
