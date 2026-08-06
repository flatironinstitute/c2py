
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

using c2py::operator""_a;

// ==================== enums =====================

// ==================== module classes =====================

// --------- class _c2py_cls_b071f713 -----------
using _c2py_cls_b071f713                                            = a_class;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_b071f713>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_b071f713> = "itertool.AClass";
static const auto _c2py_init_65e329f1                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_b071f713>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_b071f713>    = c2py::pyfkw_constructor<_c2py_init_65e329f1>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_b071f713> = _c2py_init_65e329f1.doc(R"DOC()DOC");
// data
static auto const _c2py_fun_91ad014b =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_b071f713 const &self) -> decltype(auto) { return self.data(); }, "self")};

// values
static auto const _c2py_fun_a1044fa9 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_b071f713 const &self) -> decltype(auto) { return self.values(); }, "self")};

static const auto _c2py_doc_91ad014b = _c2py_fun_91ad014b.doc(R"DOC()DOC");
static const auto _c2py_doc_a1044fa9 = _c2py_fun_a1044fa9.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_b071f713>[] = {
   PMDF("data", 91ad014b),
   PMDF("values", a1044fa9),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_34698e4f = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_b071f713>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_b071f713::v, _c2py_cls_b071f713>("v", _c2py_doc_member_34698e4f),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_b071f713> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_b071f713>;

// ==================== module functions ====================

// trf
static auto const _c2py_fun_971d8eff = c2py::dispatcher_f_kw_t{c2py::cfun([](int n) { return trf(n); }, "n")};

static const auto _c2py_doc_971d8eff = _c2py_fun_971d8eff.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("trf", 971d8eff),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "itertool",        /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_itertool() {

  if (not c2py::check_python_version("itertool")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_b071f713>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_b071f713, "AClass");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
