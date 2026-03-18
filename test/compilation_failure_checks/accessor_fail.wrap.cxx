
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

template <> constexpr bool c2py::is_wrapped<A> = true;
template <> constexpr bool c2py::is_wrapped<B> = true;

// ==================== enums =====================

// ==================== module classes =====================

template <> inline constexpr auto c2py::tp_name<A> = "accessor_fail.A";
static auto init_0                                 = c2py::dispatcher_c_kw_t{c2py::c_constructor<A, int>("i")};
template <> constexpr initproc c2py::tp_init<A>    = c2py::pyfkw_constructor<init_0>;
template <> const std::string c2py::tp_ctor_doc<A> = init_0.doc(R"DOC()DOC");
// m
static auto const fun_0 = c2py::dispatcher_f_kw_t{c2py::cmethod([](A &self) -> decltype(auto) { return self.m(); }, "self")};

static const auto doc_d_0 = fun_0.doc(R"DOC()DOC");

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<A>[] = {
   {"m", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_0 = R"DOC()DOC";

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<A>[] = {c2py::getsetdef_from_member<&A::i, A>("i", doc_member_0),

                                              {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<A>      = R"DOC()DOC" + c2py::tp_ctor_doc<A>;
template <> inline constexpr auto c2py::tp_name<B> = "accessor_fail.B";

static int synth_constructor_0(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing B.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<B> *)self)->_c = new B{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing B from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<B> *)self)->_c);
  de("a1", self_c.a1, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<B> = synth_constructor_0;

template <>
const std::string c2py::tp_ctor_doc<B> = c2py::replace_tags(R"DOC(Synthesized constructor with the following keyword arguments:

Parameters
----------
a1 : {par_0}, default=A{5}

)DOC",
                                                            "par", {c2py::python_typename<A>()});

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<B>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_1 = R"DOC()DOC";
static PyObject *prop_get_dict_0(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<B> *)self)->_c);
  c2py::pydict dic;
  dic["a1"] = self_c.a1;
  return dic.new_ref();
}

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<B>[] = {c2py::getsetdef_from_member<&B::a1, B>("a1", doc_member_1),
                                              {"__dict__", (getter)prop_get_dict_0, nullptr, "", nullptr},
                                              {nullptr, nullptr, nullptr, nullptr, nullptr}};

template <> const std::string c2py::tp_doc<B> = R"DOC()DOC" + c2py::tp_ctor_doc<B>;

// ==================== module functions ====================

//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "accessor_fail",   /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_accessor_fail() {

  if (not c2py::check_python_version("accessor_fail")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<A>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<B>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;
  c2py::add_type_object_to_main<A>("A", m, conv_table);
  c2py::add_type_object_to_main<B>("B", m, conv_table);

  return m;
}
#endif
// CLAIR_WRAP_GEN
