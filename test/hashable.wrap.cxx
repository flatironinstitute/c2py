
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

// --------- class _c2py_cls_b7c193b0 -----------
using _c2py_cls_b7c193b0                                            = N::cls_hashable;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_b7c193b0>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_b7c193b0> = "hashable.ClsHashable";
static const auto _c2py_init_ece3c8dd =
   c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_b7c193b0>(), c2py::c_constructor<_c2py_cls_b7c193b0, int>("v")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_b7c193b0>    = c2py::pyfkw_constructor<_c2py_init_ece3c8dd>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_b7c193b0> = _c2py_init_ece3c8dd.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_b7c193b0>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_d5972725 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_b7c193b0>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_b7c193b0::value, _c2py_cls_b7c193b0>("value", _c2py_doc_member_d5972725),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_b7c193b0> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_b7c193b0>;
// --------- class _c2py_cls_3a379fba -----------
using _c2py_cls_3a379fba                                            = N::cls_not_hashable;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_3a379fba>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_3a379fba> = "hashable.ClsNotHashable";
static const auto _c2py_init_cca5231c =
   c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_3a379fba>(), c2py::c_constructor<_c2py_cls_3a379fba, int>("v")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_3a379fba>    = c2py::pyfkw_constructor<_c2py_init_cca5231c>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_3a379fba> = _c2py_init_cca5231c.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_3a379fba>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_ac147d6f = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_3a379fba>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_3a379fba::value, _c2py_cls_3a379fba>("value", _c2py_doc_member_ac147d6f),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_3a379fba> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_3a379fba>;

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
                                        "hashable",        /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_hashable() {

  if (not c2py::check_python_version("hashable")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_b7c193b0>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_3a379fba>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_b7c193b0, "ClsHashable");
  _add_type(_c2py_cls_3a379fba, "ClsNotHashable");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
