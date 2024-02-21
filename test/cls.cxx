//#pragma GCC visibility push(hidden)
//#pragma CLANG visibility push(hidden)

#ifdef __clang__
//#pragma clang diagnostic ignored "-W#warnings"
#pragma clang diagnostic ignored "-Wmissing-field-initializers"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wcast-function-type"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wcpp"
#endif

//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
#include "c2py/c2py.hpp"
#include "cls.cpp"

using namespace c2py;
using c2py::operator"" _a;

template <> constexpr bool c2py::is_wrapped<A> = true;

static_assert(c2py::concepts::IsConvertible<int>);

// =============== struct A =====================
namespace c2py {
  template <> inline const std::string cpp_name<A> = "[C++ A]";

  template <> constexpr auto tp_name<A>       = "cls.A";
  template <> constexpr const char *tp_doc<A> = "Doc A ";
} // namespace c2py
//      --- constructor ---
static int init_1(PyObject *self, PyObject *args, PyObject *kwargs) {
  static dispatcher_c_kw_t ovs = {c_constructor<A>(), c_maker<A>(&maker_A, "i")};
  return ovs(self, args, kwargs);
};

template <> constexpr initproc c2py::tp_init<A> = &init_1;

// //      --- methods  ---
// static PyObject *fun_A1(PyObject *self, PyObject *args, PyObject *kwargs) {
//   static dispatcher_f_kw_t ovs = {cfun(c2py::castm<int>(&A::f), "x")};
//   return ovs(self, args, kwargs);
// };

// static PyObject *fun_A2(PyObject *self, PyObject *args, PyObject *kwargs) {
//   static dispatcher_f_kw_t ovs = {cfun(&A::tpl<int>, "i"), cfun(&A::tpl<double>, "i")};
//   return ovs(self, args, kwargs);
// };

// // friend or any rewriting ...
// static PyObject *fun_A4(PyObject *self, PyObject *args, PyObject *kwargs) {
//   static auto rewrite          = [](A const &a) -> int { return a_friend(a); };
//   static dispatcher_f_kw_t ovs = {cfun(rewrite, "a")};
//   return ovs(self, args, kwargs);
// };

static const auto fun_B1 = dispatcher_f_kw_t{cfun(c2py::castm<int>(&A::f), "x")};
static const auto fun_B2 = dispatcher_f_kw_t{cfun(&A::tpl<int>, "i"), cfun(&A::tpl<double>, "i")};
static const auto fun_B4 = dispatcher_f_kw_t{cfun([](A const &a) -> int { return a_friend(a); }, "a")};

static const auto doc11 = std::string{"doc11"};

//  --- method table ---
template <>
PyMethodDef c2py::tp_methods<A>[] = {
   {"f", (PyCFunction)c2py::pyfkw<fun_B1>, METH_VARARGS | METH_KEYWORDS, doc11.c_str()}, // put doc out if too long
   //  {"f", (PyCFunction)fun_A1, METH_VARARGS | METH_KEYWORDS, "Doc f2"},   // put doc out if too long
   {"tpl", (PyCFunction)c2py::pyfkw<fun_B2>, METH_VARARGS | METH_KEYWORDS, "Doc f2"}, // put doc out if too long
   //  {"tpl", (PyCFunction)fun_A2, METH_VARARGS | METH_KEYWORDS, "Doc f2"}, // put doc out if too long
   {"__getstate__", c2py::getstate_tuple<A>, METH_NOARGS, "  "},
   {"__setstate__", c2py::setstate_tuple<A>, METH_O, "  "},
   //   {"__reduce__", c2py::reduce_tuple<A>, METH_VARARGS, "  "},
   {NULL} // Sentinel
};

//      --- members and properties  ---

static PyObject *prop_get_A_1(PyObject *self, void *) {
  static dispatcher_f_kw_t ovs = {cfun(&A::get_prop)};
  return ovs(self, nullptr, nullptr);
}

static int prop_set_A_1(PyObject *self, PyObject *value, void *) {
  if (value == NULL) return (PyErr_SetString(PyExc_AttributeError, "Cannot delete the attribute p of object A"), -1);
  static dispatcher_f_kw_t ovs = {cfun(&A::set_prop, "i")};
  ovs(self, pyref(PyTuple_Pack(1, value)), nullptr);
  return 0;
}

template <>
constinit PyGetSetDef c2py::tp_getset<A>[] = {{"k", get_member<&A::k, A>, set_member<&A::k, A>, "Doc of k member", nullptr}, //
                                              {"p", (getter)prop_get_A_1, (setter)prop_set_A_1, "Doc of p prop", nullptr},   //
                                              {NULL}};

//   ---  [] -----

// FIXME : template ...
//Py_ssize_t A_size(PyObject *self) { return py_converter<A>::py2c(self).size(); }

static PyObject *fun_3(PyObject *self, PyObject *key) {
  //static dispatcher_f_kw_t ovs = {cfun(castmc<int>(&A::operator[]), "x")};
  //pyref args2 = (PyTuple_Check(key) ? cpp2py::pyref::borrowed(key) : pyref(PyTuple_Pack(1, key))); // FIXME losing time
  //return ovs(self, args2, nullptr);
  //auto rewrite = [](A const &a, int i) ->decltype(auto) { return a[i];};
  //static auto ovs = dispatcher_t<c2py::pycfun2>{c2py::cfun2(cast<A const&, int>(rewrite))};
  static auto ovs = dispatcher_t<c2py::pycfun23>{c2py::cfun2(getitem<A, int>)};
  //static auto ovs = dispatcher_t<c2py::pycfun23>{c2py::cfun2(pycastmc<int>(&A::operator[]))};
  //pyref args2 = (PyTuple_Check(key) ? cpp2py::pyref::borrowed(key) : pyref(PyTuple_Pack(1, key))); // FIXME losing time
  return ovs(self, key);
};

static int fun_3b(PyObject *self, PyObject *key, PyObject *val) {
  //static dispatcher_f_kw_t ovs = {cfun(rewrite, "o", "i", "v")};
  static auto ovs = dispatcher_t<c2py::pycfun23>{c2py::cfun2(setitem<A, int>)};
  //  static auto ovs = dispatcher_t<c2py::pycfun23>{c2py::cfun2(static_cast<void(*)(A&, int, int)>(rewrite))};
  //pyref args2 =  pyref(PyTuple_Pack(3, self, key, val)); // FIXME losing time
  //ovs(self, args2, nullptr);
  pyref r = ovs(self, key, val);
  return (r == nullptr ? -1 : 0);
}

// FIXME
// ptr -> tp_operatorindex : if 0, nothing, else put size as template function...
template <> PyMappingMethods c2py::tp_as_mapping<A> = {tpxx_size<A>, fun_3, fun_3b};
//template <> PyMappingMethods tp_as_mapping<A> = {A_size, fun_3, NULL};

// ----() ----

static PyObject *fun_call(PyObject *self, PyObject *args, PyObject *kwargs) {
  static dispatcher_f_kw_t ovs = {cfun(static_cast<int (A::*)(int)>(&A::operator()), "i"),
                                  cfun(static_cast<int (A::*)(int, int) const>(&A::operator()), "i", "j")};
  return ovs(self, args, kwargs);
};

template <> constexpr ternaryfunc c2py::tp_call<A> = fun_call;

// ------ arithmetic ---

template <> struct c2py::arithmetic<A, c2py::OpName::Add> : std::tuple<triplet<A, A, A>, triplet<A, A, int>> {};
template <> struct c2py::arithmetic<A, c2py::OpName::Sub> : std::tuple<triplet<A, A, A>> {};

template <> constexpr PyNumberMethods *c2py::tp_as_number<A> = &c2py::tp_as_number_impl<A>;

//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"a_friend", (PyCFunction)c2py::pyfkw<fun_B4>, METH_VARARGS | METH_KEYWORDS, "Doc eval"}, // put doc out if too long
   //   {"a_friend", (PyCFunction)fun_A4, METH_VARARGS | METH_KEYWORDS, "Doc eval"}, // put doc out if too long
   //   {"__reduce_reconstructor__A", (PyCFunction)c2py::reconstructor_tuple<A>, METH_VARARGS , "  "},
   {NULL} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "cls", /* name of module */
                                        "DOC MODULE",                 /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods};

//--------------------- defines ---------------------

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_cls() {

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&wrap_pytype<A>) < 0) return NULL;
  wrap_pytype<A>.tp_new = PyType_GenericNew;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  CLAIR_C2PY_ADD_TYPE_OBJECT(A, "A");

  return m;
}
