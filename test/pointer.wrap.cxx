
// C.f. https://numpy.org/doc/1.21/reference/c-api/array.html#importing-the-api
#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API
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

#include "c2py/c2py.hpp"
#include "pointer.cpp"

using c2py::operator"" _a;

// ==================== Wrapped classes =====================

#ifndef C2PY_HXX_DECLARATION_pointer_GUARDS
#define C2PY_HXX_DECLARATION_pointer_GUARDS
template <> constexpr bool c2py::is_wrapped<a_struct> = true;
#endif

// ==================== enums =====================

// ==================== module classes =====================

template <> inline const std::string c2py::cpp_name<a_struct>   = "a_struct";
template <> inline constexpr auto c2py::tp_name<a_struct>       = "pointer.AStruct";
template <> inline constexpr const char *c2py::tp_doc<a_struct> = R"DOC(   * a: int = 30)DOC";

static int synth_constructor_0(PyObject *self, PyObject *args, PyObject *kwargs) {
  if (args and PyTuple_Check(args) and (PyTuple_Size(args) > 0)) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing a_struct.\nNo positional arguments allowed. Use keywords arguments"));
    return -1;
  }
  c2py::pydict_extractor de{kwargs};
  try {
    ((c2py::wrap<a_struct> *)self)->_c = new a_struct{};
  } catch (std::exception const &e) {
    PyErr_SetString(PyExc_RuntimeError, ("Error in constructing a_struct from a Python dict.\n   "s + e.what()).c_str());
    return -1;
  }
  auto &self_c = *(((c2py::wrap<a_struct> *)self)->_c);
  de("a", self_c.a, true);
  return de.check();
}

template <> constexpr initproc c2py::tp_init<a_struct> = synth_constructor_0;

// ----- Method table ----
template <>
PyMethodDef c2py::tp_methods<a_struct>[] = {

   {nullptr, nullptr, 0, nullptr} // Sentinel
};

constexpr auto doc_member_0 = R"DOC()DOC";
static PyObject *prop_get_dict_0(PyObject *self, void *) {
  auto &self_c = *(((c2py::wrap<a_struct> *)self)->_c);
  c2py::pydict dic;
  dic["a"] = self_c.a;
  return dic.new_ref();
}

// ----- Method table ----

template <>
constinit PyGetSetDef c2py::tp_getset<a_struct>[] = {c2py::getsetdef_from_member<&a_struct::a, a_struct>("a", doc_member_0),
                                                     {"__dict__", (getter)prop_get_dict_0, nullptr, "", nullptr},
                                                     {nullptr, nullptr, nullptr, nullptr, nullptr}};

// ==================== module functions ====================

// inc
static auto const fun_0 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<a_struct *>(&inc), "a")};

// read
static auto const fun_1 = c2py::dispatcher_f_kw_t{c2py::cfun(c2py::cast<const a_struct *>(&read), "a")};

static const auto doc_d_0 = fun_0.doc({R"DOC(   )DOC"});
static const auto doc_d_1 = fun_1.doc({R"DOC(   )DOC"});
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"inc", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {"read", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "pointer",         /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_pointer() {

  if (not c2py::check_python_version("pointer")) return NULL;

    // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<c2py::py_range>) < 0) return NULL;
  if (PyType_Ready(&c2py::wrap_pytype<a_struct>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;
  CLAIR_C2PY_ADD_TYPE_OBJECT(a_struct, "AStruct");

  return m;
}
