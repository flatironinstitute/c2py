
// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#ifndef CLAIR_C2PY_WRAP_GEN
#ifdef __clang__
// #pragma clang diagnostic ignored "-W#warnings"
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wcast-function-type"
#pragma GCC diagnostic ignored "-Wcpp"
#endif

#define C2PY_VERSION_MAJOR 1
#define C2PY_VERSION_MINOR 0

#include <c2py/c2py.hpp>
#include <c2py/version_check.hpp>

using c2py::operator""_a;

// ==================== enums =====================

template <> constexpr bool c2py::is_wrapped<A::C::E1>                            = true;
template <> const std::map<A::C::E1, std::string> c2py::enum_to_string<A::C::E1> = {{A::C::E1::a, "a"}, {A::C::E1::b, "b"}, {A::C::E1::c, "c"}};

// ==================== module classes =====================

// --------- class _c2py_cls_09b8ce31 -----------
using _c2py_cls_09b8ce31                                            = A::C;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_09b8ce31>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_09b8ce31> = "namespace.C";
static const auto _c2py_init_fc05ef85                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_09b8ce31>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_09b8ce31>    = c2py::pyfkw_constructor<_c2py_init_fc05ef85>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_09b8ce31> = _c2py_init_fc05ef85.doc(R"DOC()DOC");
// f1
static auto const _c2py_fun_cf6d434c =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_09b8ce31 &self, A::C::E1 x) -> decltype(auto) { return self.f1(x); }, "self", "x")};

static const auto _c2py_doc_cf6d434c = _c2py_fun_cf6d434c.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_09b8ce31>[] = {
   PMDF("f1", cf6d434c),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_09b8ce31> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_09b8ce31>;

// ==================== module functions ====================

// funcA
static auto const _c2py_fun_16cbc632 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return A::funcA(); })};

// funcB
static auto const _c2py_fun_15cbc49f = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return A::B::funcB(); })};

static const auto _c2py_doc_16cbc632 = _c2py_fun_16cbc632.doc(R"DOC()DOC");
static const auto _c2py_doc_15cbc49f = _c2py_fun_15cbc49f.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("funcA", 16cbc632),
   PMDF("funcB", 15cbc49f),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "namespace",                                   /* name of module */
                                        R"RAWDOC(Test for namespace filtering)RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_namespace() {

  if (not c2py::check_python_version("namespace")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_09b8ce31>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_09b8ce31, "C");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
