
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

// --------- class _c2py_cls_2cba381d -----------
using _c2py_cls_2cba381d                                            = N::my_base;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_2cba381d>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_2cba381d> = "tpl_derived.MyBase";
static const auto _c2py_init_9380993c                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_2cba381d>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_2cba381d>    = c2py::pyfkw_constructor<_c2py_init_9380993c>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_2cba381d> = _c2py_init_9380993c.doc(R"DOC()DOC");
// f_base
static auto const _c2py_fun_b6c53a47 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_2cba381d &self, int u) -> decltype(auto) { return self.f_base(u); }, "self", "u")};

static const auto _c2py_doc_b6c53a47 = _c2py_fun_b6c53a47.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_2cba381d>[] = {
   PMDF("f_base", b6c53a47),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_2cba381d> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_2cba381d>;
// --------- class _c2py_cls_4f367130 -----------
using _c2py_cls_4f367130                                            = N::my_class;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_4f367130>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_4f367130> = "tpl_derived.MyClass";
static const auto _c2py_init_e5593014 =
   c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_4f367130>(), c2py::c_constructor<_c2py_cls_4f367130, int>("u")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_4f367130>    = c2py::pyfkw_constructor<_c2py_init_e5593014>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_4f367130> = _c2py_init_e5593014.doc(R"DOC()DOC");
// get
static auto const _c2py_fun_e1eb4958 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_4f367130 const &self, long i) -> decltype(auto) { return self.get(i); }, "self", "i")};

static const auto _c2py_doc_e1eb4958 = _c2py_fun_e1eb4958.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_4f367130>[] = {
   PMDF("get", e1eb4958),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_7d6922bf = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_4f367130>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_4f367130::i, _c2py_cls_4f367130>("i", _c2py_doc_member_7d6922bf),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_4f367130> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_4f367130>;

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
                                        "tpl_derived",     /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_tpl_derived() {

  if (not c2py::check_python_version("tpl_derived")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_2cba381d>) < 0) return NULL;
  c2py::wrap_pytype<_c2py_cls_4f367130>.tp_base = &c2py::wrap_pytype<N::my_base>;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_4f367130>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_2cba381d, "MyBase");
  _add_type(_c2py_cls_4f367130, "MyClass");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
