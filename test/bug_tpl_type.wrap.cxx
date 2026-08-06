
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

// ==================== module classes =====================

// --------- class _c2py_cls_c60bf9f2 -----------
using _c2py_cls_c60bf9f2                                            = C;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c60bf9f2>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c60bf9f2> = "bug_tpl_type.C";
static const auto _c2py_init_12b36bc6                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c60bf9f2>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c60bf9f2>    = c2py::pyfkw_constructor<_c2py_init_12b36bc6>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c60bf9f2> = _c2py_init_12b36bc6.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c60bf9f2>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_c60bf9f2> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c60bf9f2>;
// --------- class _c2py_cls_a8fa5425 -----------
using _c2py_cls_a8fa5425                                            = A<3>;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_a8fa5425>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_a8fa5425> = "bug_tpl_type.A3";
static const auto _c2py_init_f4341508                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_a8fa5425>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_a8fa5425>    = c2py::pyfkw_constructor<_c2py_init_f4341508>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_a8fa5425> = _c2py_init_f4341508.doc(R"DOC()DOC");
// f
static auto const _c2py_fun_ba6a31c9 = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_a8fa5425 &self, std::vector<std::array<int, 3>> v) -> decltype(auto) { return self.f(v); }, "self", "v")};

static const auto _c2py_doc_ba6a31c9 = _c2py_fun_ba6a31c9.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_a8fa5425>[] = {
   PMDF("f", ba6a31c9),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_a8fa5425> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_a8fa5425>;
// --------- class _c2py_cls_d22e259e -----------
using _c2py_cls_d22e259e                                            = B<int>;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_d22e259e>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_d22e259e> = "bug_tpl_type.Bi";
static const auto _c2py_init_a7666d90                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_d22e259e>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_d22e259e>    = c2py::pyfkw_constructor<_c2py_init_a7666d90>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_d22e259e> = _c2py_init_a7666d90.doc(R"DOC()DOC");
// f
static auto const _c2py_fun_3ef8638c = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_d22e259e &self, std::vector<std::array<int, 3>> v) -> decltype(auto) { return self.f(v); }, "self", "v")};

static const auto _c2py_doc_3ef8638c = _c2py_fun_3ef8638c.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_d22e259e>[] = {
   PMDF("f", 3ef8638c),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_d22e259e> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_d22e259e>;

// ==================== module functions ====================

//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "bug_tpl_type",    /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_bug_tpl_type() {

  if (not c2py::check_python_version("bug_tpl_type")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c60bf9f2>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_a8fa5425>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_d22e259e>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_c60bf9f2, "C");
  _add_type(_c2py_cls_a8fa5425, "A3");
  _add_type(_c2py_cls_d22e259e, "Bi");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
