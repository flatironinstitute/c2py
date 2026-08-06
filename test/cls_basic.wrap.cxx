
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

// --------- class _c2py_cls_c40bf6cc -----------
using _c2py_cls_c40bf6cc                                            = A;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c40bf6cc>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c40bf6cc> = "cls_basic.A";
static const auto _c2py_init_185b847b =
   c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c40bf6cc>(), c2py::c_constructor<_c2py_cls_c40bf6cc, int>("i")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c40bf6cc>    = c2py::pyfkw_constructor<_c2py_init_185b847b>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c40bf6cc> = _c2py_init_185b847b.doc(R"DOC()DOC");
// __call__
static auto const _c2py_fun_0dda3dc8 = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_c40bf6cc &self, int i) -> decltype(auto) { return self.operator()(i); }, "self", "i"),
   c2py::cmethod([](_c2py_cls_c40bf6cc const &self, int i, int j) -> decltype(auto) { return self.operator()(i, j); }, "self", "i", "j")};

template <> inline constexpr ternaryfunc c2py::tp_call<_c2py_cls_c40bf6cc> = c2py::pyfkw<_c2py_fun_0dda3dc8>;

// clone
static auto const _c2py_fun_b6c59305 = c2py::dispatcher_f_kw_t{c2py::cmethod(&clone<A>, "x")};

// f
static auto const _c2py_fun_ecb8a08a =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c40bf6cc &self, int x) -> decltype(auto) { return self.f(x); }, "self", "x")};

// f_w_alias
static auto const _c2py_fun_b5908327 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c40bf6cc const &self, long i) -> decltype(auto) { return self.f_w_alias(i); }, "self", "i")};

// h
static auto const _c2py_fun_deb88a80 = c2py::dispatcher_f_kw_t{c2py::cmethod(c2py::cast<const A &, int>(&hhh), "a", "j")};

// m1
static auto const _c2py_fun_e98e832a =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c40bf6cc &self, double x) -> decltype(auto) { return self.m1(x); }, "self", "x"),
                           c2py::cmethod([](_c2py_cls_c40bf6cc &self, int x) -> decltype(auto) { return self.template m1<int>(x); }, "self", "x")};

// no_prop
static auto const _c2py_fun_db210b39 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c40bf6cc &self) -> decltype(auto) { return self.no_prop(); }, "self")};

// static_method
static auto const _c2py_fun_9f113b42 = c2py::dispatcher_f_kw_t{c2py::cfun([](int i) { return _c2py_cls_c40bf6cc::static_method(i); }, "i")};

// tpl
static auto const _c2py_fun_b6b30180 = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_c40bf6cc &self, double x) -> decltype(auto) { return self.template tpl<double>(x); }, "self", "x")};

static const auto _c2py_doc_0dda3dc8 = _c2py_fun_0dda3dc8.doc(R"DOC()DOC");
static const auto _c2py_doc_b6c59305 = _c2py_fun_b6c59305.doc(R"DOC()DOC");
static const auto _c2py_doc_ecb8a08a = _c2py_fun_ecb8a08a.doc(R"DOC()DOC");
static const auto _c2py_doc_b5908327 = _c2py_fun_b5908327.doc(R"DOC()DOC");
static const auto _c2py_doc_deb88a80 = _c2py_fun_deb88a80.doc(R"DOC()DOC");
static const auto _c2py_doc_e98e832a = _c2py_fun_e98e832a.doc(R"DOC()DOC");
static const auto _c2py_doc_db210b39 = _c2py_fun_db210b39.doc(R"DOC()DOC");
static const auto _c2py_doc_9f113b42 = _c2py_fun_9f113b42.doc(R"DOC()DOC");
static const auto _c2py_doc_b6b30180 = _c2py_fun_b6b30180.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c40bf6cc>[] = {
   PMDF("clone", b6c59305),
   PMDF("f", ecb8a08a),
   PMDF("f_w_alias", b5908327),
   PMDF("h", deb88a80),
   PMDF("m1", e98e832a),
   PMDF("no_prop", db210b39),
   PMDF("static_method", 9f113b42, METH_STATIC),
   PMDF("tpl", b6b30180),
   {"__getstate__", c2py::getstate_tuple<_c2py_cls_c40bf6cc>, METH_NOARGS, ""},
   {"__setstate__", c2py::setstate_tuple<_c2py_cls_c40bf6cc>, METH_O, ""},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_e1b88f39 = R"DOC()DOC";
constexpr auto _c2py_doc_member_2349250e = R"DOC()DOC";
constexpr auto _c2py_doc_member_fcb8b9ba = R"DOC()DOC";
static constexpr auto prop_doc_5ef69a98  = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_c40bf6cc>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_c40bf6cc::k, _c2py_cls_c40bf6cc>("k", _c2py_doc_member_e1b88f39),
   {"k_immutable", c2py::get_member<&_c2py_cls_c40bf6cc::k_immutable, _c2py_cls_c40bf6cc>, nullptr, _c2py_doc_member_2349250e, nullptr},
   c2py::getsetdef_from_member<&_c2py_cls_c40bf6cc::v, _c2py_cls_c40bf6cc>("v", _c2py_doc_member_fcb8b9ba),
   {"prop1", c2py::getter_from_method<c2py::castm<>(&A::prop1)>, nullptr, prop_doc_5ef69a98, nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

static PyObject *getitem_185b847b(PyObject *self, PyObject *key) {
  static c2py::dispatcher_t<c2py::pycfun23> disp = {c2py::cfun2(c2py::getitem<_c2py_cls_c40bf6cc, int>)};
  return disp(self, key);
}

static int setitem_185b847b(PyObject *self, PyObject *key, PyObject *val) {
  static c2py::dispatcher_t<c2py::pycfun23> disp{c2py::cfun2(c2py::setitem<_c2py_cls_c40bf6cc, int>)};
  c2py::pyref r = disp(self, key, val);
  return (r == nullptr ? -1 : 0);
}

template <> PyMappingMethods c2py::tp_as_mapping<_c2py_cls_c40bf6cc> = {c2py::tpxx_size<_c2py_cls_c40bf6cc>, getitem_185b847b, setitem_185b847b};

template <> struct c2py::arithmetic<_c2py_cls_c40bf6cc, c2py::OpName::Add> : std::tuple<std::pair<A, A>, std::pair<A, int>> {};

template <> struct c2py::arithmetic<_c2py_cls_c40bf6cc, c2py::OpName::Sub> : std::tuple<std::pair<A, A>> {};

template <> constexpr PyNumberMethods *c2py::tp_as_number<_c2py_cls_c40bf6cc> = &c2py::tp_as_number_impl<_c2py_cls_c40bf6cc>;

template <> const std::string c2py::tp_doc<_c2py_cls_c40bf6cc> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_c40bf6cc>;
// --------- class _c2py_cls_c085e5d4 -----------
using _c2py_cls_c085e5d4                                            = dummy_class;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_c085e5d4>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_c085e5d4> = "cls_basic.DummyClass";
static const auto _c2py_init_8dfb0132                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_c085e5d4>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_c085e5d4>    = c2py::pyfkw_constructor<_c2py_init_8dfb0132>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_c085e5d4> = _c2py_init_8dfb0132.doc(R"DOC()DOC");
// do_thing
static auto const _c2py_fun_c99f5a32 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_c085e5d4 &self, double x) -> decltype(auto) { return self.do_thing(x); }, "self", "x")};

static const auto _c2py_doc_c99f5a32 = _c2py_fun_c99f5a32.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_c085e5d4>[] = {
   PMDF("do_thing", c99f5a32),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <>
const std::string c2py::tp_doc<_c2py_cls_c085e5d4> =
   R"DOC(test implementation outside of class)DOC" + std::string{"\n\n----------\n\n"} + c2py::tp_ctor_doc<_c2py_cls_c085e5d4>;
// --------- class _c2py_cls_f62177da -----------
using _c2py_cls_f62177da                                            = some_class;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_f62177da>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_f62177da> = "cls_basic.renamed_class";
static const auto _c2py_init_ee707880                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_f62177da>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_f62177da>    = c2py::pyfkw_constructor<_c2py_init_ee707880>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_f62177da> = _c2py_init_ee707880.doc(R"DOC()DOC");
// renamed_method
static auto const _c2py_fun_363c6244 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_f62177da &self, int y) -> decltype(auto) { return self.some_method(y); }, "self", "y")};

static const auto _c2py_doc_363c6244 = _c2py_fun_363c6244.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_f62177da>[] = {
   PMDF("renamed_method", 363c6244),
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

constexpr auto _c2py_doc_member_39d055a2 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_f62177da>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_f62177da::x, _c2py_cls_f62177da>("x", _c2py_doc_member_39d055a2),

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_f62177da> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_f62177da>;
// --------- class _c2py_cls_dd4185b8 -----------
using _c2py_cls_dd4185b8                                            = ns::B;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_dd4185b8>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_dd4185b8> = "cls_basic.B";
static const auto _c2py_init_6bb5837a                               = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_dd4185b8>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_dd4185b8>    = c2py::pyfkw_constructor<_c2py_init_6bb5837a>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_dd4185b8> = _c2py_init_6bb5837a.doc(R"DOC()DOC");

// ----- Method table ----
// clang-format off
template <> PyMethodDef c2py::tp_methods<_c2py_cls_dd4185b8>[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};
// clang-format on

template <> const std::string c2py::tp_doc<_c2py_cls_dd4185b8> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_dd4185b8>;

// ==================== module functions ====================

// a_friend
static auto const _c2py_fun_dfa469b1 = c2py::dispatcher_f_kw_t{c2py::cfun([](const A &a) { return a_friend(a); }, "a")};

// b_friend
static auto const _c2py_fun_8b3ce2ba = c2py::dispatcher_f_kw_t{c2py::cfun([](const A &a) { return b_friend(a); }, "a")};

// inline_friend
static auto const _c2py_fun_a89d8bf9 = c2py::dispatcher_f_kw_t{c2py::cfun([](const ns::B &b) { return inline_friend(b); }, "b")};

// mutate_a
static auto const _c2py_fun_eb84626f = c2py::dispatcher_f_kw_t{c2py::cfun([](A &a) { return mutate_a(a); }, "a")};

// my_module_init
static auto const _c2py_fun_4c11a6d7 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return my_module_init(); })};

// nop
static auto const _c2py_fun_25b1963e = c2py::dispatcher_f_kw_t{c2py::cfun([](const A &a) { return nop(a); }, "a")};

static const auto _c2py_doc_dfa469b1 = _c2py_fun_dfa469b1.doc(R"DOC()DOC");
static const auto _c2py_doc_8b3ce2ba = _c2py_fun_8b3ce2ba.doc(R"DOC()DOC");
static const auto _c2py_doc_a89d8bf9 = _c2py_fun_a89d8bf9.doc(R"DOC()DOC");
static const auto _c2py_doc_eb84626f = _c2py_fun_eb84626f.doc(R"DOC()DOC");
static const auto _c2py_doc_4c11a6d7 = _c2py_fun_4c11a6d7.doc(R"DOC()DOC");
static const auto _c2py_doc_25b1963e = _c2py_fun_25b1963e.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

// clang-format off
static PyMethodDef module_methods[] = {
   PMDF("a_friend", dfa469b1),
   PMDF("b_friend", 8b3ce2ba),
   PMDF("inline_friend", a89d8bf9),
   PMDF("mutate_a", eb84626f),
   PMDF("my_module_init", 4c11a6d7),
   PMDF("nop", 25b1963e),
   {nullptr, nullptr, 0, nullptr}  // Sentinel
};
// clang-format on

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "cls_basic", /* name of module */
                                        R"RAWDOC(A long documentation of this nice module
  with multiple lines
and a lot of text
)RAWDOC",                                            /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_cls_basic() {

  if (not c2py::check_python_version("cls_basic")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c40bf6cc>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_c085e5d4>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_f62177da>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_dd4185b8>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  if (not c2py::register_internal_types()) return NULL;
#define _add_type(T, N)                                                                                                                              \
  if (not c2py::add_type_object_to_main<T>(N, m)) return NULL
  _add_type(_c2py_cls_c40bf6cc, "A");
  _add_type(_c2py_cls_c085e5d4, "DummyClass");
  _add_type(_c2py_cls_f62177da, "renamed_class");
  _add_type(_c2py_cls_dd4185b8, "B");
#undef _add_type

  // Initialization of the module
  my_module_init();

  return m;
}
#endif
// CLAIR_WRAP_GEN
