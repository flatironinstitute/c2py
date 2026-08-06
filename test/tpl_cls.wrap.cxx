
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

// --------- class _c2py_cls_926ca08d -----------
using _c2py_cls_926ca08d                                            = A<int>;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_926ca08d>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_926ca08d> = "tpl_cls.AA";
static const auto _c2py_init_e4adbd59 =
   c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_926ca08d>(), c2py::c_constructor<_c2py_cls_926ca08d, int>("i")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_926ca08d>    = c2py::pyfkw_constructor<_c2py_init_e4adbd59>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_926ca08d> = _c2py_init_e4adbd59.doc(R"DOC()DOC");
// __call__
static auto const _c2py_fun_1fd6a459 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_926ca08d const &self, int i) -> decltype(auto) { return self.operator()(i); }, "self", "i")};

template <> inline constexpr ternaryfunc c2py::tp_call<_c2py_cls_926ca08d> = c2py::pyfkw<_c2py_fun_1fd6a459>;

// call
static auto const _c2py_fun_2f9925e1 = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_926ca08d &self, const long &x) -> decltype(auto) { return self.template call<double, const long &>(x); }, "self", "x")};

// convert
static auto const _c2py_fun_90cde300 = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_926ca08d &self, double x) -> decltype(auto) { return self.template convert<int, double>(x); }, "self", "x")};

// f
static auto const _c2py_fun_0adcdf01 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_926ca08d &self, int x) -> decltype(auto) { return self.f(x); }, "self", "x")};

// g
static auto const _c2py_fun_09dcdd6e =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_926ca08d &self, int x) -> decltype(auto) { return self.g(x); }, "self", "x")};

// tpl
static auto const _c2py_fun_3b1e2a57 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_926ca08d &self, int x) -> decltype(auto) { return self.template tpl<int>(x); }, "self", "x")};

// with_default_arg
static auto const _c2py_fun_a94e8b34 = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_926ca08d &self, int x) -> decltype(auto) { return self.with_default_arg(x); }, "self", "x"_a = 42)};

static const auto _c2py_doc_1fd6a459 = _c2py_fun_1fd6a459.doc(R"DOC()DOC");
static const auto _c2py_doc_2f9925e1 = _c2py_fun_2f9925e1.doc(R"DOC()DOC");
static const auto _c2py_doc_90cde300 = _c2py_fun_90cde300.doc(R"DOC()DOC");
static const auto _c2py_doc_0adcdf01 = _c2py_fun_0adcdf01.doc(R"DOC()DOC");
static const auto _c2py_doc_09dcdd6e = _c2py_fun_09dcdd6e.doc(R"DOC()DOC");
static const auto _c2py_doc_3b1e2a57 = _c2py_fun_3b1e2a57.doc(R"DOC()DOC");
static const auto _c2py_doc_a94e8b34 = _c2py_fun_a94e8b34.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_926ca08d>[] = {
   PMDF("call", 2f9925e1),
   PMDF("convert", 90cde300),
   PMDF("f", 0adcdf01),
   PMDF("g", 09dcdd6e),
   PMDF("tpl", 3b1e2a57),
   PMDF("with_default_arg", a94e8b34),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_05dcd722 = R"DOC()DOC";
constexpr auto _c2py_doc_member_df30c669 = R"DOC()DOC";
constexpr auto _c2py_doc_member_fadcc5d1 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_926ca08d>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_926ca08d::k, _c2py_cls_926ca08d>("k", _c2py_doc_member_05dcd722),
   {"k_immutable", c2py::get_member<&_c2py_cls_926ca08d::k_immutable, _c2py_cls_926ca08d>, nullptr, _c2py_doc_member_df30c669, nullptr},
   c2py::getsetdef_from_member<&_c2py_cls_926ca08d::v, _c2py_cls_926ca08d>("v", _c2py_doc_member_fadcc5d1),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

static PyObject *getitem_e4adbd59(PyObject *self, PyObject *key) {
  static c2py::dispatcher_t<c2py::pycfun23> disp = {c2py::cfun2(c2py::getitem<_c2py_cls_926ca08d, int>)};
  return disp(self, key);
}

template <> PyMappingMethods c2py::tp_as_mapping<_c2py_cls_926ca08d> = {nullptr, getitem_e4adbd59, nullptr};

template <> const std::string c2py::tp_doc<_c2py_cls_926ca08d> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_926ca08d>;

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
                                        "tpl_cls",         /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_tpl_cls() {

  if (not c2py::check_python_version("tpl_cls")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_926ca08d>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_926ca08d, "AA");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
