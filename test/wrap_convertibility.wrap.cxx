
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

// --------- class _c2py_cls_c40bf6cc -----------
using _c2py_cls_c40bf6cc                                            = A;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c40bf6cc>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c40bf6cc> = "wrap_convertibility.A";
static const auto _c2py_init_185b847b                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c40bf6cc, int>("x")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c40bf6cc>    = c2py::pyfkw_constructor<_c2py_init_185b847b>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c40bf6cc> = _c2py_init_185b847b.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c40bf6cc>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_eeb8a3b0 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_c40bf6cc>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_c40bf6cc::x, _c2py_cls_c40bf6cc>("x", _c2py_doc_member_eeb8a3b0),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_c40bf6cc> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c40bf6cc>;
// --------- class _c2py_cls_c70bfb85 -----------
using _c2py_cls_c70bfb85                                            = B;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c70bfb85>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c70bfb85> = "wrap_convertibility.B";
static const auto _c2py_init_4ca6916b                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c70bfb85>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c70bfb85>    = c2py::pyfkw_constructor<_c2py_init_4ca6916b>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c70bfb85> = _c2py_init_4ca6916b.doc(R"DOC()DOC");
// first
static auto const _c2py_fun_bb5c11f1 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c70bfb85 const &self) -> decltype(auto) { return self.first(); }, "self")};

// get_data
static auto const _c2py_fun_b15a5ad0 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c70bfb85 const &self) -> decltype(auto) { return self.get_data(); }, "self")};

// push
static auto const _c2py_fun_c478df2d =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c70bfb85 &self, A a) -> decltype(auto) { return self.push(a); }, "self", "a")};

// sum_x
static auto const _c2py_fun_00119d27 = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_c70bfb85 const &self, const std::vector<A> &v) -> decltype(auto) { return self.sum_x(v); }, "self", "v")};

static const auto _c2py_doc_bb5c11f1 = _c2py_fun_bb5c11f1.doc(R"DOC()DOC");
static const auto _c2py_doc_b15a5ad0 = _c2py_fun_b15a5ad0.doc(R"DOC()DOC");
static const auto _c2py_doc_c478df2d = _c2py_fun_c478df2d.doc(R"DOC()DOC");
static const auto _c2py_doc_00119d27 = _c2py_fun_00119d27.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c70bfb85>[] = {
   PMDF("first", bb5c11f1),
   PMDF("get_data", b15a5ad0),
   PMDF("push", c478df2d),
   PMDF("sum_x", 00119d27),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_c70bfb85> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c70bfb85>;

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
                                        "wrap_convertibility", /* name of module */
                                        R"RAWDOC()RAWDOC",     /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_wrap_convertibility() {

  if (not c2py::check_python_version("wrap_convertibility")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c40bf6cc>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c70bfb85>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_c40bf6cc, "A");
  _add_type(_c2py_cls_c70bfb85, "B");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
