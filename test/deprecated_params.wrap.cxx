
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

// --------- class _c2py_cls_3f2fea45 -----------
using _c2py_cls_3f2fea45                                            = MyClass;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_3f2fea45>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_3f2fea45> = "deprecated_params.MyClass";
static const auto _c2py_init_10cef024 =
   c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_3f2fea45, int>("v")}.with_deprecated_params({{"old_v", "v"}});
template <> constexpr initproc c2py::tp_init<_c2py_cls_3f2fea45>    = c2py::pyfkw_constructor<_c2py_init_10cef024>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_3f2fea45> = _c2py_init_10cef024.doc(R"DOC()DOC");
// get_val
static auto const _c2py_fun_9822b277 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_3f2fea45 const &self) -> decltype(auto) { return self.get_val(); }, "self")};

static const auto _c2py_doc_9822b277 = _c2py_fun_9822b277.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_3f2fea45>[] = {
   PMDF("get_val", 9822b277),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_2e25f86c = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_3f2fea45>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_3f2fea45::val, _c2py_cls_3f2fea45>("val", _c2py_doc_member_2e25f86c),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_3f2fea45> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_3f2fea45>;

// ==================== module functions ====================

// f_renamed
static auto const _c2py_fun_6b23fb88 =
   c2py::dispatcher_f_kw_t{c2py::cfun([](int x, int y) { return f_renamed(x, y); }, "x", "y"_a = 10)}.with_deprecated_params({{"old_x", "x"}});

// g_renamed
static auto const _c2py_fun_d44f27cf =
   c2py::dispatcher_f_kw_t{c2py::cfun([](int a, int b) { return g_renamed(a, b); }, "a", "b")}.with_deprecated_params(
      {{"old_a", "a"}, {"old_b", "b"}});

static const auto _c2py_doc_6b23fb88 = _c2py_fun_6b23fb88.doc(R"DOC()DOC");
static const auto _c2py_doc_d44f27cf = _c2py_fun_d44f27cf.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("f_renamed", 6b23fb88),
   PMDF("g_renamed", d44f27cf),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "deprecated_params", /* name of module */
                                        R"RAWDOC()RAWDOC",   /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_deprecated_params() {

  if (not c2py::check_python_version("deprecated_params")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_3f2fea45>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_3f2fea45, "MyClass");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
