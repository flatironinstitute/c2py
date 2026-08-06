
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

// --------- class _c2py_cls_7780ab00 -----------
using _c2py_cls_7780ab00                                            = N::cls_equal;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_7780ab00>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_7780ab00> = "comparison.ClsEqual";
static const auto _c2py_init_00d539c5                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_7780ab00>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_7780ab00>    = c2py::pyfkw_constructor<_c2py_init_00d539c5>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_7780ab00> = _c2py_init_00d539c5.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_7780ab00>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_71e81615 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_7780ab00>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_7780ab00::value, _c2py_cls_7780ab00>("value", _c2py_doc_member_71e81615),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_7780ab00> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_7780ab00>;
// --------- class _c2py_cls_518d7fb6 -----------
using _c2py_cls_518d7fb6                                            = N::cls_equal2;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_518d7fb6>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_518d7fb6> = "comparison.ClsEqual2";
static const auto _c2py_init_1a720fa3                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_518d7fb6>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_518d7fb6>    = c2py::pyfkw_constructor<_c2py_init_1a720fa3>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_518d7fb6> = _c2py_init_1a720fa3.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_518d7fb6>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_71f6ad43 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_518d7fb6>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_518d7fb6::value, _c2py_cls_518d7fb6>("value", _c2py_doc_member_71f6ad43),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_518d7fb6> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_518d7fb6>;
// --------- class _c2py_cls_579fa1bf -----------
using _c2py_cls_579fa1bf                                            = N::cls_comp;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_579fa1bf>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_579fa1bf> = "comparison.ClsComp";
static const auto _c2py_init_45e01a3d                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_579fa1bf>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_579fa1bf>    = c2py::pyfkw_constructor<_c2py_init_45e01a3d>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_579fa1bf> = _c2py_init_45e01a3d.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_579fa1bf>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_422b1db4 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_579fa1bf>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_579fa1bf::value, _c2py_cls_579fa1bf>("value", _c2py_doc_member_422b1db4),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_579fa1bf> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_579fa1bf>;

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
                                        "comparison",      /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_comparison() {

  if (not c2py::check_python_version("comparison")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_7780ab00>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_518d7fb6>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_579fa1bf>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_7780ab00, "ClsEqual");
  _add_type(_c2py_cls_518d7fb6, "ClsEqual2");
  _add_type(_c2py_cls_579fa1bf, "ClsComp");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
