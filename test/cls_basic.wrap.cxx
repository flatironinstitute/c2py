
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

// ==================== Wrapped classes =====================

template <> constexpr bool c2py::is_wrapped<A>           = true;
template <> constexpr bool c2py::is_wrapped<dummy_class> = true;
template <> constexpr bool c2py::is_wrapped<some_class>  = true;

// ==================== enums =====================

// ==================== module classes =====================

template <> inline constexpr auto c2py::tp_name<A> = "cls_basic.A";
static auto init_0                                 = c2py::dispatcher_c_kw_t{c2py::c_constructor<A>(), c2py::c_constructor<A, int>("i")};
template <> constexpr initproc c2py::tp_init<A>    = c2py::pyfkw_constructor<init_0>;
template <> const std::string c2py::tp_ctor_doc<A> = init_0.doc(R"DOC()DOC");
// __call__
static auto const fun_0 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](A &self, int i) -> decltype(auto) { return self.operator()(i); }, "self", "i"),
                           c2py::cmethod([](A const &self, int i, int j) -> decltype(auto) { return self.operator()(i, j); }, "self", "i", "j")};

template <> inline constexpr ternaryfunc c2py::tp_call<A> = c2py::pyfkw<fun_0>;

// clone
static auto const fun_1 = c2py::dispatcher_f_kw_t{c2py::cmethod(&clone<A>, "x")};

// f
static auto const fun_2 = c2py::dispatcher_f_kw_t{c2py::cmethod([](A &self, int x) -> decltype(auto) { return self.f(x); }, "self", "x")};

// f_w_alias
static auto const fun_3 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](A const &self, long i) -> decltype(auto) { return self.f_w_alias(i); }, "self", "i")};

// h
static auto const fun_4 = c2py::dispatcher_f_kw_t{c2py::cmethod(c2py::cast<const A &, int>(&hhh), "a", "j")};

// m1
static auto const fun_5 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](A &self, double x) -> decltype(auto) { return self.m1(x); }, "self", "x"),
                           c2py::cmethod([](A &self, int x) -> decltype(auto) { return self.template m1<int>(x); }, "self", "x")};

// no_prop
static auto const fun_6 = c2py::dispatcher_f_kw_t{c2py::cmethod([](A &self) -> decltype(auto) { return self.no_prop(); }, "self")};

// static_method
static auto const fun_7 = c2py::dispatcher_f_kw_t{c2py::cfun([](int i) { return A::static_method(i); }, "i")};

// tpl
static auto const fun_8 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](A &self, double x) -> decltype(auto) { return self.template tpl<double>(x); }, "self", "x")};

static const auto doc_d_0 = fun_0.doc(R"DOC()DOC");
static const auto doc_d_1 = fun_1.doc(R"DOC()DOC");
static const auto doc_d_2 = fun_2.doc(R"DOC()DOC");
static const auto doc_d_3 = fun_3.doc(R"DOC()DOC");
static const auto doc_d_4 = fun_4.doc(R"DOC()DOC");
static const auto doc_d_5 = fun_5.doc(R"DOC()DOC");
static const auto doc_d_6 = fun_6.doc(R"DOC()DOC");
static const auto doc_d_7 = fun_7.doc(R"DOC()DOC");
static const auto doc_d_8 = fun_8.doc(R"DOC()DOC");

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<A>[] = {
   {"clone", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {"f", (PyCFunction)c2py::pyfkw<fun_2>, METH_VARARGS | METH_KEYWORDS, doc_d_2.c_str()},
   {"f_w_alias", (PyCFunction)c2py::pyfkw<fun_3>, METH_VARARGS | METH_KEYWORDS, doc_d_3.c_str()},
   {"h", (PyCFunction)c2py::pyfkw<fun_4>, METH_VARARGS | METH_KEYWORDS, doc_d_4.c_str()},
   {"m1", (PyCFunction)c2py::pyfkw<fun_5>, METH_VARARGS | METH_KEYWORDS, doc_d_5.c_str()},
   {"no_prop", (PyCFunction)c2py::pyfkw<fun_6>, METH_VARARGS | METH_KEYWORDS, doc_d_6.c_str()},
   {"static_method", (PyCFunction)c2py::pyfkw<fun_7>, METH_VARARGS | METH_KEYWORDS | METH_STATIC, doc_d_7.c_str()},
   {"tpl", (PyCFunction)c2py::pyfkw<fun_8>, METH_VARARGS | METH_KEYWORDS, doc_d_8.c_str()},
   {"__getstate__", c2py::getstate_tuple<A>, METH_NOARGS, ""},
   {"__setstate__", c2py::setstate_tuple<A>, METH_O, ""},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_0      = R"DOC()DOC";
constexpr auto doc_member_1      = R"DOC()DOC";
constexpr auto doc_member_2      = R"DOC()DOC";
static constexpr auto prop_doc_0 = R"DOC()DOC";

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<A>[] = {c2py::getsetdef_from_member<&A::k, A>("k", doc_member_0),
                                              {"k_immutable", c2py::get_member<&A::k_immutable, A>, nullptr, doc_member_1, nullptr},
                                              c2py::getsetdef_from_member<&A::v, A>("v", doc_member_2),
                                              {"prop1", c2py::getter_from_method<c2py::castm<>(&A::prop1)>, nullptr, prop_doc_0, nullptr},
                                              {nullptr, nullptr, nullptr, nullptr, nullptr}};

static PyObject *getitem_0(PyObject *self, PyObject *key) {
  static c2py::dispatcher_t<c2py::pycfun23> disp = {c2py::cfun2(c2py::getitem<A, int>)};
  return disp(self, key);
}

static int setitem_0(PyObject *self, PyObject *key, PyObject *val) {
  static c2py::dispatcher_t<c2py::pycfun23> disp{c2py::cfun2(c2py::setitem<A, int>)};
  c2py::pyref r = disp(self, key, val);
  return (r == nullptr ? -1 : 0);
}

template <> PyMappingMethods c2py::tp_as_mapping<A> = {c2py::tpxx_size<A>, getitem_0, setitem_0};

template <> struct c2py::arithmetic<A, c2py::OpName::Add> : std::tuple<std::pair<A, A>, std::pair<A, int>> {};

template <> struct c2py::arithmetic<A, c2py::OpName::Sub> : std::tuple<std::pair<A, A>> {};

template <> constexpr PyNumberMethods *c2py::tp_as_number<A> = &c2py::tp_as_number_impl<A>;

template <> const std::string c2py::tp_doc<A>                = R"DOC()DOC" + c2py::tp_ctor_doc<A>;
template <> inline constexpr auto c2py::tp_name<dummy_class> = "cls_basic.DummyClass";
static auto init_1                                           = c2py::dispatcher_c_kw_t{c2py::c_constructor<dummy_class>()};
template <> constexpr initproc c2py::tp_init<dummy_class>    = c2py::pyfkw_constructor<init_1>;
template <> const std::string c2py::tp_ctor_doc<dummy_class> = init_1.doc(R"DOC()DOC");
// do_thing
static auto const fun_9 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](dummy_class &self, double x) -> decltype(auto) { return self.do_thing(x); }, "self", "x")};

static const auto doc_d_9 = fun_9.doc(R"DOC()DOC");

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<dummy_class>[] = {
   {"do_thing", (PyCFunction)c2py::pyfkw<fun_9>, METH_VARARGS | METH_KEYWORDS, doc_d_9.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<dummy_class>[] = {

   {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <>
const std::string c2py::tp_doc<dummy_class> =
   R"DOC(test implementation outside of class)DOC" + std::string{"\n\n----------\n\n"} + c2py::tp_ctor_doc<dummy_class>;
template <> inline constexpr auto c2py::tp_name<some_class> = "cls_basic.renamed_class";
static auto init_2                                          = c2py::dispatcher_c_kw_t{c2py::c_constructor<some_class>()};
template <> constexpr initproc c2py::tp_init<some_class>    = c2py::pyfkw_constructor<init_2>;
template <> const std::string c2py::tp_ctor_doc<some_class> = init_2.doc(R"DOC()DOC");
// renamed_method
static auto const fun_10 =
   c2py::dispatcher_f_kw_t{c2py::cmethod([](some_class &self, int y) -> decltype(auto) { return self.some_method(y); }, "self", "y")};

static const auto doc_d_10 = fun_10.doc(R"DOC()DOC");

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<some_class>[] = {
   {"renamed_method", (PyCFunction)c2py::pyfkw<fun_10>, METH_VARARGS | METH_KEYWORDS, doc_d_10.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_3 = R"DOC()DOC";

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<some_class>[] = {c2py::getsetdef_from_member<&some_class::x, some_class>("x", doc_member_3),

                                                       {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<some_class> = R"DOC()DOC" + c2py::tp_ctor_doc<some_class>;

// ==================== module functions ====================

// my_module_init
static auto const fun_11 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return my_module_init(); })};

// nop
static auto const fun_12 = c2py::dispatcher_f_kw_t{c2py::cfun([](const A &a) { return nop(a); }, "a")};

static const auto doc_d_11 = fun_11.doc(R"DOC()DOC");
static const auto doc_d_12 = fun_12.doc(R"DOC()DOC");
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"my_module_init", (PyCFunction)c2py::pyfkw<fun_11>, METH_VARARGS | METH_KEYWORDS, doc_d_11.c_str()},
   {"nop", (PyCFunction)c2py::pyfkw<fun_12>, METH_VARARGS | METH_KEYWORDS, doc_d_12.c_str()},
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
  if (PyType_Ready(&c2py::wrap_pytype<A>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<dummy_class>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<some_class>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;
  c2py::add_type_object_to_main<A>("A", m, conv_table);
  c2py::add_type_object_to_main<dummy_class>("DummyClass", m, conv_table);
  c2py::add_type_object_to_main<some_class>("renamed_class", m, conv_table);

  // Initialization of the module
  my_module_init();

  return m;
}
#endif
// CLAIR_WRAP_GEN
