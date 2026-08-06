
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

// --------- class _c2py_cls_c70bfb85 -----------
using _c2py_cls_c70bfb85                                            = B;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c70bfb85>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c70bfb85> = "cls_der.B";
static const auto _c2py_init_4ca6916b                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c70bfb85, int>("i")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c70bfb85>    = c2py::pyfkw_constructor<_c2py_init_4ca6916b>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c70bfb85> = _c2py_init_4ca6916b.doc(R"DOC()DOC");
// b
static auto const _c2py_fun_feecfe75 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c70bfb85 &self, int u) -> decltype(auto) { return self.b(u); }, "self", "u")};

static const auto _c2py_doc_feecfe75 = _c2py_fun_feecfe75.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c70bfb85>[] = {
   PMDF("b", feecfe75),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_6420c702 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_c70bfb85>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_c70bfb85::ib, _c2py_cls_c70bfb85>("ib", _c2py_doc_member_6420c702),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_c70bfb85> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c70bfb85>;
// --------- class _c2py_cls_c40bf6cc -----------
using _c2py_cls_c40bf6cc                                            = A;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c40bf6cc>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c40bf6cc> = "cls_der.A";
static const auto _c2py_init_185b847b                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c40bf6cc, int>("i")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c40bf6cc>    = c2py::pyfkw_constructor<_c2py_init_185b847b>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c40bf6cc> = _c2py_init_185b847b.doc(R"DOC()DOC");
// a
static auto const _c2py_fun_e7b898ab =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c40bf6cc &self, int i, int j) -> decltype(auto) { return self.a(i, j); }, "self", "i", "j")};

static const auto _c2py_doc_e7b898ab = _c2py_fun_e7b898ab.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c40bf6cc>[] = {
   PMDF("a", e7b898ab),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_c40bf6cc> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c40bf6cc>;
// --------- class _c2py_cls_c10bf213 -----------
using _c2py_cls_c10bf213                                            = D;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c10bf213>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c10bf213> = "cls_der.D";
static const auto _c2py_init_8e33de8a                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c10bf213, int>("i")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c10bf213>    = c2py::pyfkw_constructor<_c2py_init_8e33de8a>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c10bf213> = _c2py_init_8e33de8a.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c10bf213>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

static constexpr auto prop_doc_b8f57919 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_c10bf213>[] = {

   {"cc", c2py::getter_from_method_B<D, c2py::castmc<>(&C::cc)>, (setter)c2py::setter_from_method_B<D, &C::set_cc>, prop_doc_b8f57919,
    (void *)"Cannot delete the attribute cc"},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_c10bf213> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c10bf213>;

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
                                        "cls_der",         /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_cls_der() {

  if (not c2py::check_python_version("cls_der")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c70bfb85>) < 0) return NULL;
  c2py::wrap_pytype<_c2py_cls_c40bf6cc>.tp_base = &c2py::wrap_pytype<B>;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c40bf6cc>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c10bf213>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_c70bfb85, "B");
  _add_type(_c2py_cls_c40bf6cc, "A");
  _add_type(_c2py_cls_c10bf213, "D");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
