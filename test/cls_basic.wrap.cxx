
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

#define C2PY_VERSION_MAJOR 0
#define C2PY_VERSION_MINOR 1

#include <c2py/c2py.hpp>

using c2py::operator""_a;

// ==================== enums =====================

// ==================== module classes =====================

// --------- class _c2py_cls_0 -----------
using _c2py_cls_0                                            = A;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_0>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_0> = "cls_basic.A";
static auto _c2py_init_0 = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_0>(), c2py::c_constructor<_c2py_cls_0, int>("i")};
template <> constexpr initproc c2py::tp_init<_c2py_cls_0>    = c2py::pyfkw_constructor<_c2py_init_0>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_0> = _c2py_init_0.doc(R"DOC()DOC");
// __call__
static auto const _c2py_fun_0 = c2py::dispatcher_f_kw_t{
   c2py::cmethod([](_c2py_cls_0 &self, int i) -> decltype(auto) { return self.operator()(i); }, "self", "i"),
   c2py::cmethod([](_c2py_cls_0 const &self, int i, int j) -> decltype(auto) { return self.operator()(i, j); }, "self", "i", "j")};

template <> inline constexpr ternaryfunc c2py::tp_call<_c2py_cls_0> = c2py::pyfkw<_c2py_fun_0>;

// clone
static auto const _c2py_fun_1 = c2py::dispatcher_f_kw_t{c2py::cmethod(&clone<A>, "x")};

// f
static auto const _c2py_fun_2 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_0 &self, int x) -> decltype(auto) { return self.f(x); }, "self", "x")};

// f_w_alias
static auto const _c2py_fun_3 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_0 const &self, long i) -> decltype(auto) { return self.f_w_alias(i); }, "self", "i")};

// h
static auto const _c2py_fun_4 = c2py::dispatcher_f_kw_t{c2py::cmethod(c2py::cast<const A &, int>(&hhh), "a", "j")};

// m1
static auto const _c2py_fun_5 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_0 &self, double x) -> decltype(auto) { return self.m1(x); }, "self", "x"),
                           c2py::cmethod([](_c2py_cls_0 &self, int x) -> decltype(auto) { return self.template m1<int>(x); }, "self", "x")};

// no_prop
static auto const _c2py_fun_6 = c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_0 &self) -> decltype(auto) { return self.no_prop(); }, "self")};

// static_method
static auto const _c2py_fun_7 = c2py::dispatcher_f_kw_t{c2py::cfun([](int i) { return _c2py_cls_0::static_method(i); }, "i")};

// tpl
static auto const _c2py_fun_8 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_0 &self, double x) -> decltype(auto) { return self.template tpl<double>(x); }, "self", "x")};

static const auto _c2py_doc_0 = _c2py_fun_0.doc(R"DOC()DOC");
static const auto _c2py_doc_1 = _c2py_fun_1.doc(R"DOC()DOC");
static const auto _c2py_doc_2 = _c2py_fun_2.doc(R"DOC()DOC");
static const auto _c2py_doc_3 = _c2py_fun_3.doc(R"DOC()DOC");
static const auto _c2py_doc_4 = _c2py_fun_4.doc(R"DOC()DOC");
static const auto _c2py_doc_5 = _c2py_fun_5.doc(R"DOC()DOC");
static const auto _c2py_doc_6 = _c2py_fun_6.doc(R"DOC()DOC");
static const auto _c2py_doc_7 = _c2py_fun_7.doc(R"DOC()DOC");
static const auto _c2py_doc_8 = _c2py_fun_8.doc(R"DOC()DOC");

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<_c2py_cls_0>[] = {
   {"clone", (PyCFunction)c2py::pyfkw<_c2py_fun_1>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_1.c_str()},
   {"f", (PyCFunction)c2py::pyfkw<_c2py_fun_2>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_2.c_str()},
   {"f_w_alias", (PyCFunction)c2py::pyfkw<_c2py_fun_3>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_3.c_str()},
   {"h", (PyCFunction)c2py::pyfkw<_c2py_fun_4>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_4.c_str()},
   {"m1", (PyCFunction)c2py::pyfkw<_c2py_fun_5>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_5.c_str()},
   {"no_prop", (PyCFunction)c2py::pyfkw<_c2py_fun_6>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_6.c_str()},
   {"static_method", (PyCFunction)c2py::pyfkw<_c2py_fun_7>, METH_VARARGS | METH_KEYWORDS | METH_STATIC, _c2py_doc_7.c_str()},
   {"tpl", (PyCFunction)c2py::pyfkw<_c2py_fun_8>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_8.c_str()},
   {"__getstate__", c2py::getstate_tuple<_c2py_cls_0>, METH_NOARGS, ""},
   {"__setstate__", c2py::setstate_tuple<_c2py_cls_0>, METH_O, ""},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto _c2py_doc_member_0 = R"DOC()DOC";
constexpr auto _c2py_doc_member_1 = R"DOC()DOC";
constexpr auto _c2py_doc_member_2 = R"DOC()DOC";
static constexpr auto prop_doc_0  = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_0>[] = {
   c2py::getsetdef_from_member<&_c2py_cls_0::k, _c2py_cls_0>("k", _c2py_doc_member_0),
   {"k_immutable", c2py::get_member<&_c2py_cls_0::k_immutable, _c2py_cls_0>, nullptr, _c2py_doc_member_1, nullptr},
   c2py::getsetdef_from_member<&_c2py_cls_0::v, _c2py_cls_0>("v", _c2py_doc_member_2),
   {"prop1", c2py::getter_from_method<c2py::castm<>(&A::prop1)>, nullptr, prop_doc_0, nullptr},
   {nullptr, nullptr, nullptr, nullptr, nullptr}};

static PyObject *getitem_0(PyObject *self, PyObject *key) {
  static c2py::dispatcher_t<c2py::pycfun23> disp = {c2py::cfun2(c2py::getitem<_c2py_cls_0, int>)};
  return disp(self, key);
}

static int setitem_0(PyObject *self, PyObject *key, PyObject *val) {
  static c2py::dispatcher_t<c2py::pycfun23> disp{c2py::cfun2(c2py::setitem<_c2py_cls_0, int>)};
  c2py::pyref r = disp(self, key, val);
  return (r == nullptr ? -1 : 0);
}

template <> PyMappingMethods c2py::tp_as_mapping<_c2py_cls_0> = {c2py::tpxx_size<_c2py_cls_0>, getitem_0, setitem_0};

template <> struct c2py::arithmetic<_c2py_cls_0, c2py::OpName::Add> : std::tuple<std::pair<A, A>, std::pair<A, int>> {};

template <> struct c2py::arithmetic<_c2py_cls_0, c2py::OpName::Sub> : std::tuple<std::pair<A, A>> {};

template <> constexpr PyNumberMethods *c2py::tp_as_number<_c2py_cls_0> = &c2py::tp_as_number_impl<_c2py_cls_0>;

template <> const std::string c2py::tp_doc<_c2py_cls_0> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_0>;
// --------- class _c2py_cls_1 -----------
using _c2py_cls_1                                            = dummy_class;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_1>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_1> = "cls_basic.DummyClass";
static auto _c2py_init_1                                     = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_1>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_1>    = c2py::pyfkw_constructor<_c2py_init_1>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_1> = _c2py_init_1.doc(R"DOC()DOC");
// do_thing
static auto const _c2py_fun_9 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_1 &self, double x) -> decltype(auto) { return self.do_thing(x); }, "self", "x")};

static const auto _c2py_doc_9 = _c2py_fun_9.doc(R"DOC()DOC");

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<_c2py_cls_1>[] = {
   {"do_thing", (PyCFunction)c2py::pyfkw<_c2py_fun_9>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_9.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

template <>
const std::string c2py::tp_doc<_c2py_cls_1> =
   R"DOC(test implementation outside of class)DOC" + std::string{"\n\n----------\n\n"} + c2py::tp_ctor_doc<_c2py_cls_1>;
// --------- class _c2py_cls_2 -----------
using _c2py_cls_2                                            = some_class;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_2>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_2> = "cls_basic.renamed_class";
static auto _c2py_init_2                                     = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_2>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_2>    = c2py::pyfkw_constructor<_c2py_init_2>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_2> = _c2py_init_2.doc(R"DOC()DOC");
// renamed_method
static auto const _c2py_fun_10 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](_c2py_cls_2 &self, int y) -> decltype(auto) { return self.some_method(y); }, "self", "y")};

static const auto _c2py_doc_10 = _c2py_fun_10.doc(R"DOC()DOC");

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<_c2py_cls_2>[] = {
   {"renamed_method", (PyCFunction)c2py::pyfkw<_c2py_fun_10>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_10.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto _c2py_doc_member_3 = R"DOC()DOC";

// ----- Member and property table ----

template <>
constinit PyGetSetDef c2py::tp_getset<_c2py_cls_2>[] = {c2py::getsetdef_from_member<&_c2py_cls_2::x, _c2py_cls_2>("x", _c2py_doc_member_3),

                                                        {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<_c2py_cls_2> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_2>;
// --------- class _c2py_cls_3 -----------
using _c2py_cls_3                                            = ns::B;
template <> constexpr bool c2py::is_wrapped<_c2py_cls_3>     = true;
template <> inline constexpr auto c2py::tp_name<_c2py_cls_3> = "cls_basic.B";
static auto _c2py_init_3                                     = c2py::dispatcher_c_kw_t{c2py::c_constructor<_c2py_cls_3>()};
template <> constexpr initproc c2py::tp_init<_c2py_cls_3>    = c2py::pyfkw_constructor<_c2py_init_3>;
template <> const std::string c2py::tp_ctor_doc<_c2py_cls_3> = _c2py_init_3.doc(R"DOC()DOC");

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<_c2py_cls_3>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

template <> const std::string c2py::tp_doc<_c2py_cls_3> = R"DOC()DOC" + c2py::tp_ctor_doc<_c2py_cls_3>;

// ==================== module functions ====================

// a_friend
static auto const _c2py_fun_11 = c2py::dispatcher_f_kw_t{c2py::cfun([](const A &a) { return a_friend(a); }, "a")};

// b_friend
static auto const _c2py_fun_12 = c2py::dispatcher_f_kw_t{c2py::cfun([](const A &a) { return b_friend(a); }, "a")};

// inline_friend
static auto const _c2py_fun_13 = c2py::dispatcher_f_kw_t{c2py::cfun([](const ns::B &b) { return ns::inline_friend(b); }, "b")};

// my_module_init
static auto const _c2py_fun_14 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return my_module_init(); })};

// nop
static auto const _c2py_fun_15 = c2py::dispatcher_f_kw_t{c2py::cfun([](const A &a) { return nop(a); }, "a")};

static const auto _c2py_doc_11 = _c2py_fun_11.doc(R"DOC()DOC");
static const auto _c2py_doc_12 = _c2py_fun_12.doc(R"DOC()DOC");
static const auto _c2py_doc_13 = _c2py_fun_13.doc(R"DOC()DOC");
static const auto _c2py_doc_14 = _c2py_fun_14.doc(R"DOC()DOC");
static const auto _c2py_doc_15 = _c2py_fun_15.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"a_friend", (PyCFunction)c2py::pyfkw<_c2py_fun_11>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_11.c_str()},
   {"b_friend", (PyCFunction)c2py::pyfkw<_c2py_fun_12>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_12.c_str()},
   {"inline_friend", (PyCFunction)c2py::pyfkw<_c2py_fun_13>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_13.c_str()},
   {"my_module_init", (PyCFunction)c2py::pyfkw<_c2py_fun_14>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_14.c_str()},
   {"nop", (PyCFunction)c2py::pyfkw<_c2py_fun_15>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_15.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

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

  if (PyType_Ready(&c2py::wrap_pytype<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_0>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_1>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_2>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<_c2py_cls_3>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;
#define _add_type(T, N) c2py::add_type_object_to_main<T>(N, m, conv_table)
  _add_type(_c2py_cls_0, "A");
  _add_type(_c2py_cls_1, "DummyClass");
  _add_type(_c2py_cls_2, "renamed_class");
  _add_type(_c2py_cls_3, "B");
#undef _add_type

  // Initialization of the module
  my_module_init();

  return m;
}
#endif
// CLAIR_WRAP_GEN
