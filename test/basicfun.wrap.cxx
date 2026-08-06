
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
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c40bf6cc> = "basicfun.A";
static const auto _c2py_init_185b847b                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c40bf6cc>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c40bf6cc>    = c2py::pyfkw_constructor<_c2py_init_185b847b>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c40bf6cc> = _c2py_init_185b847b.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c40bf6cc>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_efb8a543 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_c40bf6cc>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_c40bf6cc::y, _c2py_cls_c40bf6cc>("y", _c2py_doc_member_efb8a543),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_c40bf6cc> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c40bf6cc>;

// ==================== module functions ====================

// dd
static auto const _c2py_fun_5d1cd035 = c2py::dispatcher_f_kw_t{
   c2py::cfun([](int x, int y) { return dd(x, y); }, "x", "y"_a = 8), c2py::cfun([](int x, long y) { return dd(x, y); }, "x", "y"_a = 8),
   c2py::cfun([](int x, bool y) { return dd(x, y); }, "x", "y"_a = false),
   c2py::cfun([](int x, double z, int y) { return dd(x, z, y); }, "x", "z", "y"_a = get_arg()),
   c2py::cfun([](int x, std::string y) { return dd(x, y); }, "x", "y"_a = "blabla")};

// doc_d_1
static auto const _c2py_fun_c18df496 = c2py::dispatcher_f_kw_t{c2py::cfun([](int _p_0) { return doc_d_1(_p_0); }, "_p_0")};

// f
static auto const _c2py_fun_e30c2799 =
   c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f(x); }, "x"), c2py::cfun([](int x, int y) { return f(x, y); }, "x", "y")};

// f1
static auto const _c2py_fun_14226d78 = c2py::dispatcher_f_kw_t{c2py::cfun([](double x) { return f1(x); }, "x")};

// g
static auto const _c2py_fun_e20c2606 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x, int y) { return g(x, y); }, "x", "y"_a = 8)};

// get_arg
static auto const _c2py_fun_f0a1b024 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_arg(); })};

// h
static auto const _c2py_fun_ed0c3757 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return N::h<int>(x); }, "x")};

// hf
static auto const _c2py_fun_5b3ae223 =
   c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return f1(x); }, "x"), c2py::cfun([](long x) { return N::h<long>(x); }, "x"),
                           c2py::cfun([](double x) { return N::h<double>(x); }, "x")};

// isfinite
static auto const _c2py_fun_26129d76 = c2py::dispatcher_f_kw_t{c2py::cfun([](const dcomplex &x) { return N::isfinite(x); }, "x")};

// newf
static auto const _c2py_fun_60c7dd55 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return newf(x); }, "x")};

// non_deducible
static auto const _c2py_fun_c3a8b83a = c2py::dispatcher_f_kw_t{c2py::cfun([](double x) { return non_deducible<int, double>(x); }, "x"),
                                                               c2py::cfun([](int x) { return non_deducible<double, int>(x); }, "x")};

// ret_with_alias
static auto const _c2py_fun_ef530f42 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return ret_with_alias(); })};

// zfoo
static auto const _c2py_fun_d3a361ef = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return zfoo(x); }, "x"_a = int{}),
                                                               c2py::cfun([](std::string x) { return zfoo(x); }, "x"_a = std::string{})};

// zfwd_decl_fnt
static auto const _c2py_fun_c9d3b6cc = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return zfwd_decl_fnt(x); }, "x")};

// zz
static auto const _c2py_fun_5767fb75 = c2py::dispatcher_f_kw_t{c2py::cfun([](const A &x) { return zz<A>(x); }, "x")};

// zz_defarg_alias2
static auto const _c2py_fun_36e0a1d2 =
   c2py::dispatcher_f_kw_t{c2py::cfun([](ns::myint_t v) { return ns::zz_defarg_alias2(v); }, "v"_a = ns::myint_t{0})};

static const auto _c2py_doc_5d1cd035 = _c2py_fun_5d1cd035.doc(R"DOC()DOC");
static const auto _c2py_doc_c18df496 = _c2py_fun_c18df496.doc(R"DOC()DOC");
static const auto _c2py_doc_e30c2799 = _c2py_fun_e30c2799.doc(R"DOC()DOC");
static const auto _c2py_doc_14226d78 = _c2py_fun_14226d78.doc(R"DOC()DOC");
static const auto _c2py_doc_e20c2606 = _c2py_fun_e20c2606.doc(R"DOC()DOC");
static const auto _c2py_doc_f0a1b024 = _c2py_fun_f0a1b024.doc(R"DOC()DOC");
static const auto _c2py_doc_ed0c3757 = _c2py_fun_ed0c3757.doc(R"DOC()DOC");
static const auto _c2py_doc_5b3ae223 = _c2py_fun_5b3ae223.doc(R"DOC()DOC");
static const auto _c2py_doc_26129d76 = _c2py_fun_26129d76.doc(R"DOC()DOC");
static const auto _c2py_doc_60c7dd55 = _c2py_fun_60c7dd55.doc(R"DOC()DOC");
static const auto _c2py_doc_c3a8b83a = _c2py_fun_c3a8b83a.doc(R"DOC()DOC");
static const auto _c2py_doc_ef530f42 = _c2py_fun_ef530f42.doc(R"DOC()DOC");
static const auto _c2py_doc_d3a361ef = _c2py_fun_d3a361ef.doc(R"DOC()DOC");
static const auto _c2py_doc_c9d3b6cc = _c2py_fun_c9d3b6cc.doc(R"DOC()DOC");
static const auto _c2py_doc_5767fb75 = _c2py_fun_5767fb75.doc(R"DOC()DOC");
static const auto _c2py_doc_36e0a1d2 = _c2py_fun_36e0a1d2.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("dd", 5d1cd035),
   PMDF("doc_d_1", c18df496),
   PMDF("f", e30c2799),
   PMDF("f1", 14226d78),
   PMDF("g", e20c2606),
   PMDF("get_arg", f0a1b024),
   PMDF("h", ed0c3757),
   PMDF("hf", 5b3ae223),
   PMDF("isfinite", 26129d76),
   PMDF("newf", 60c7dd55),
   PMDF("non_deducible", c3a8b83a),
   PMDF("ret_with_alias", ef530f42),
   PMDF("zfoo", d3a361ef),
   PMDF("zfwd_decl_fnt", c9d3b6cc),
   PMDF("zz", 5767fb75),
   PMDF("zz_defarg_alias2", 36e0a1d2),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "basicfun",        /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_basicfun() {

  if (not c2py::check_python_version("basicfun")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c40bf6cc>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_c40bf6cc, "A");
#undef _add_type

  return m;
}
#endif
// CLAIR_WRAP_GEN
