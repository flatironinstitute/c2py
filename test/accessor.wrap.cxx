
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
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c40bf6cc> = "accessor.A";
static const auto _c2py_init_185b847b                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c40bf6cc, int>("i")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c40bf6cc>    = c2py::pyfkw_constructor<_c2py_init_185b847b>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c40bf6cc> = _c2py_init_185b847b.doc(R"DOC()DOC");
// get_i
static auto const _c2py_fun_8aea0668 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c40bf6cc const &self) -> decltype(auto) { return self.get_i(); }, "self")};

// m
static auto const _c2py_fun_e3b8925f =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c40bf6cc &self) -> decltype(auto) { return self.m(); }, "self")};

static const auto _c2py_doc_8aea0668 = _c2py_fun_8aea0668.doc(R"DOC()DOC");
static const auto _c2py_doc_e3b8925f = _c2py_fun_e3b8925f.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c40bf6cc>[] = {
   PMDF("get_i", 8aea0668),
   PMDF("m", e3b8925f),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_dfb88c13 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_c40bf6cc>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_c40bf6cc::i, _c2py_cls_c40bf6cc>("i", _c2py_doc_member_dfb88c13),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_c40bf6cc> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c40bf6cc>;
// --------- class _c2py_cls_c70bfb85 -----------
using _c2py_cls_c70bfb85                                            = B;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c70bfb85>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c70bfb85> = "accessor.B";
static const auto _c2py_init_4ca6916b                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c70bfb85>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c70bfb85>    = c2py::pyfkw_constructor<_c2py_init_4ca6916b>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c70bfb85> = _c2py_init_4ca6916b.doc(R"DOC()DOC");
// get_a_ref
static auto const _c2py_fun_b97a0081 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c70bfb85 &self) -> decltype(auto) { return self.get_a_ref(); }, "self")};

// get_a_ref2
static auto const _c2py_fun_ae0f19c9 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c70bfb85 &self) -> decltype(auto) { return self.get_a_ref2(); }, "self")};

// get_a_ref_switch
static auto const _c2py_fun_cd010502 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c70bfb85 &self, bool b) -> decltype(auto) { return self.get_a_ref_switch(b); }, "self", "b")};

// get_a_via_method
static auto const _c2py_fun_0c067eec =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c70bfb85 &self) -> decltype(auto) { return self.get_a_via_method(); }, "self")};

// get_i
static auto const _c2py_fun_aa5aba73 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c70bfb85 const &self, bool b) -> decltype(auto) { return self.get_i(b); }, "self", "b")};

static const auto _c2py_doc_b97a0081 = _c2py_fun_b97a0081.doc(R"DOC()DOC");
static const auto _c2py_doc_ae0f19c9 = _c2py_fun_ae0f19c9.doc(R"DOC()DOC");
static const auto _c2py_doc_cd010502 = _c2py_fun_cd010502.doc(R"DOC()DOC");
static const auto _c2py_doc_0c067eec = _c2py_fun_0c067eec.doc(R"DOC()DOC");
static const auto _c2py_doc_aa5aba73 = _c2py_fun_aa5aba73.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c70bfb85>[] = {
   PMDF("get_a_ref", b97a0081),
   PMDF("get_a_ref2", ae0f19c9),
   PMDF("get_a_ref_switch", cd010502),
   PMDF("get_a_via_method", 0c067eec),
   PMDF("get_i", aa5aba73),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_c70bfb85> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c70bfb85>;
// --------- class _c2py_cls_2e7a8214 -----------
using _c2py_cls_2e7a8214                                            = Outer;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_2e7a8214>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_2e7a8214> = "accessor.Outer";
static const auto _c2py_init_40ff178e                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_2e7a8214>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_2e7a8214>    = c2py::pyfkw_constructor<_c2py_init_40ff178e>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_2e7a8214> = _c2py_init_40ff178e.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_2e7a8214>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_24fd4943 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_2e7a8214>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_2e7a8214::a, _c2py_cls_2e7a8214>("a", _c2py_doc_member_24fd4943),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_2e7a8214> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_2e7a8214>;
// --------- class _c2py_cls_c10bf213 -----------
using _c2py_cls_c10bf213                                            = D;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c10bf213>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c10bf213> = "accessor.D";
static const auto _c2py_init_8e33de8a                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c10bf213>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c10bf213>    = c2py::pyfkw_constructor<_c2py_init_8e33de8a>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c10bf213> = _c2py_init_8e33de8a.doc(R"DOC()DOC");
// get_nested_a
static auto const _c2py_fun_0d2b1ab9 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c10bf213 const &self) -> decltype(auto) { return self.get_nested_a(); }, "self")};

static const auto _c2py_doc_0d2b1ab9 = _c2py_fun_0d2b1ab9.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c10bf213>[] = {
   PMDF("get_nested_a", 0d2b1ab9),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_c10bf213> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c10bf213>;

// ==================== module functions ====================

// f
static auto const _c2py_fun_e30c2799 = c2py::dispatcher_f_kw_t{c2py::cfun([](A &a) { return f(a); }, "a")};

static const auto _c2py_doc_e30c2799 = _c2py_fun_e30c2799.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("f", e30c2799),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "accessor",        /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_accessor() {

  if (not c2py::check_python_version("accessor")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c40bf6cc>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c70bfb85>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_2e7a8214>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c10bf213>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_c40bf6cc, "A");
  _add_type(_c2py_cls_c70bfb85, "B");
  _add_type(_c2py_cls_2e7a8214, "Outer");
  _add_type(_c2py_cls_c10bf213, "D");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
