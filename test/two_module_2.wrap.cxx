
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
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c70bfb85> = "two_module_2.B";
static const auto _c2py_init_4ca6916b                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c70bfb85>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c70bfb85>    = c2py::pyfkw_constructor<_c2py_init_4ca6916b>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c70bfb85> = _c2py_init_4ca6916b.doc(R"DOC()DOC");
// color_passthrough
static auto const _c2py_fun_2ce3cdd1 = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_c70bfb85 &self, N::Color c) -> decltype(auto) { return self.color_passthrough(c); }, "self", "c")};

// direction_passthrough
static auto const _c2py_fun_b0c36cdb = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_c70bfb85 &self, N::Direction d) -> decltype(auto) { return self.direction_passthrough(d); }, "self", "d")};

// g
static auto const _c2py_fun_f9ecf696 = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_c70bfb85 &self, int i, const N::A &a) -> decltype(auto) { return self.g(i, a); }, "self", "i", "a")};

static const auto _c2py_doc_2ce3cdd1 = _c2py_fun_2ce3cdd1.doc(R"DOC()DOC");
static const auto _c2py_doc_b0c36cdb = _c2py_fun_b0c36cdb.doc(R"DOC()DOC");
static const auto _c2py_doc_f9ecf696 = _c2py_fun_f9ecf696.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c70bfb85>[] = {
   PMDF("color_passthrough", 2ce3cdd1),
   PMDF("direction_passthrough", b0c36cdb),
   PMDF("g", f9ecf696),
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
                                        "two_module_2",    /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_two_module_2() {

  if (not c2py::check_python_version("two_module_2")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c70bfb85>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_c70bfb85, "B");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
