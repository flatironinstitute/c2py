
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

// ==================== enums =====================

// ==================== module classes =====================

// ==================== module functions ====================

// add_int16
static auto const fun_0 = c2py::dispatcher_f_kw_t{c2py::cfun([](short a, short b) { return add_int16(a, b); }, "a", "b")};

// add_uint32
static auto const fun_1 = c2py::dispatcher_f_kw_t{c2py::cfun([](unsigned int a, unsigned int b) { return add_uint32(a, b); }, "a", "b")};

// get_int16_max
static auto const fun_2 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_int16_max(); })};

// get_int16_min
static auto const fun_3 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_int16_min(); })};

// get_int32_max
static auto const fun_4 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_int32_max(); })};

// get_int32_min
static auto const fun_5 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_int32_min(); })};

// get_int64_max
static auto const fun_6 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_int64_max(); })};

// get_int64_min
static auto const fun_7 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_int64_min(); })};

// get_longlong_max
static auto const fun_8 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_longlong_max(); })};

// get_longlong_min
static auto const fun_9 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_longlong_min(); })};

// get_short_max
static auto const fun_10 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_short_max(); })};

// get_short_min
static auto const fun_11 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_short_min(); })};

// get_uint16_max
static auto const fun_12 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_uint16_max(); })};

// get_uint32_max
static auto const fun_13 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_uint32_max(); })};

// get_uint64_max
static auto const fun_14 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_uint64_max(); })};

// get_ushort_max
static auto const fun_15 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_ushort_max(); })};

// identity_int16
static auto const fun_16 = c2py::dispatcher_f_kw_t{c2py::cfun([](short x) { return identity_int16(x); }, "x")};

// identity_int32
static auto const fun_17 = c2py::dispatcher_f_kw_t{c2py::cfun([](int x) { return identity_int32(x); }, "x")};

// identity_int64
static auto const fun_18 = c2py::dispatcher_f_kw_t{c2py::cfun([](long x) { return identity_int64(x); }, "x")};

// identity_longlong
static auto const fun_19 = c2py::dispatcher_f_kw_t{c2py::cfun([](long long x) { return identity_longlong(x); }, "x")};

// identity_short
static auto const fun_20 = c2py::dispatcher_f_kw_t{c2py::cfun([](short x) { return identity_short(x); }, "x")};

// identity_size_t
static auto const fun_21 = c2py::dispatcher_f_kw_t{c2py::cfun([](unsigned long x) { return identity_size_t(x); }, "x")};

// identity_uint16
static auto const fun_22 = c2py::dispatcher_f_kw_t{c2py::cfun([](unsigned short x) { return identity_uint16(x); }, "x")};

// identity_uint32
static auto const fun_23 = c2py::dispatcher_f_kw_t{c2py::cfun([](unsigned int x) { return identity_uint32(x); }, "x")};

// identity_uint64
static auto const fun_24 = c2py::dispatcher_f_kw_t{c2py::cfun([](unsigned long x) { return identity_uint64(x); }, "x")};

// identity_ushort
static auto const fun_25 = c2py::dispatcher_f_kw_t{c2py::cfun([](unsigned short x) { return identity_ushort(x); }, "x")};

// multiply_int64
static auto const fun_26 = c2py::dispatcher_f_kw_t{c2py::cfun([](long a, long b) { return multiply_int64(a, b); }, "a", "b")};

// identity_int8
static auto const fun_27 = c2py::dispatcher_f_kw_t{c2py::cfun([](signed char x) { return identity_int8(x); }, "x")};

// identity_uint8
static auto const fun_28 = c2py::dispatcher_f_kw_t{c2py::cfun([](unsigned char x) { return identity_uint8(x); }, "x")};

// get_int8_min
static auto const fun_29 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_int8_min(); })};

// get_int8_max
static auto const fun_30 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_int8_max(); })};

// get_uint8_max
static auto const fun_31 = c2py::dispatcher_f_kw_t{c2py::cfun([]() { return get_uint8_max(); })};

static const auto doc_d_0  = fun_0.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_1  = fun_1.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_2  = fun_2.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_3  = fun_3.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_4  = fun_4.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_5  = fun_5.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_6  = fun_6.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_7  = fun_7.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_8  = fun_8.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_9  = fun_9.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_10 = fun_10.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_11 = fun_11.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_12 = fun_12.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_13 = fun_13.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_14 = fun_14.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_15 = fun_15.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_16 = fun_16.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_17 = fun_17.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_18 = fun_18.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_19 = fun_19.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_20 = fun_20.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_21 = fun_21.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_22 = fun_22.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_23 = fun_23.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_24 = fun_24.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_25 = fun_25.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_26 = fun_26.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_27 = fun_27.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_28 = fun_28.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_29 = fun_29.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_30 = fun_30.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
static const auto doc_d_31 = fun_31.doc(R"DOC()DOC", std::vector<std::string>{}, std::vector<std::string>{});
//--------------------- module function table  -----------------------------

static PyMethodDef module_methods[] = {
   {"add_int16", (PyCFunction)c2py::pyfkw<fun_0>, METH_VARARGS | METH_KEYWORDS, doc_d_0.c_str()},
   {"add_uint32", (PyCFunction)c2py::pyfkw<fun_1>, METH_VARARGS | METH_KEYWORDS, doc_d_1.c_str()},
   {"get_int16_max", (PyCFunction)c2py::pyfkw<fun_2>, METH_VARARGS | METH_KEYWORDS, doc_d_2.c_str()},
   {"get_int16_min", (PyCFunction)c2py::pyfkw<fun_3>, METH_VARARGS | METH_KEYWORDS, doc_d_3.c_str()},
   {"get_int32_max", (PyCFunction)c2py::pyfkw<fun_4>, METH_VARARGS | METH_KEYWORDS, doc_d_4.c_str()},
   {"get_int32_min", (PyCFunction)c2py::pyfkw<fun_5>, METH_VARARGS | METH_KEYWORDS, doc_d_5.c_str()},
   {"get_int64_max", (PyCFunction)c2py::pyfkw<fun_6>, METH_VARARGS | METH_KEYWORDS, doc_d_6.c_str()},
   {"get_int64_min", (PyCFunction)c2py::pyfkw<fun_7>, METH_VARARGS | METH_KEYWORDS, doc_d_7.c_str()},
   {"get_longlong_max", (PyCFunction)c2py::pyfkw<fun_8>, METH_VARARGS | METH_KEYWORDS, doc_d_8.c_str()},
   {"get_longlong_min", (PyCFunction)c2py::pyfkw<fun_9>, METH_VARARGS | METH_KEYWORDS, doc_d_9.c_str()},
   {"get_short_max", (PyCFunction)c2py::pyfkw<fun_10>, METH_VARARGS | METH_KEYWORDS, doc_d_10.c_str()},
   {"get_short_min", (PyCFunction)c2py::pyfkw<fun_11>, METH_VARARGS | METH_KEYWORDS, doc_d_11.c_str()},
   {"get_uint16_max", (PyCFunction)c2py::pyfkw<fun_12>, METH_VARARGS | METH_KEYWORDS, doc_d_12.c_str()},
   {"get_uint32_max", (PyCFunction)c2py::pyfkw<fun_13>, METH_VARARGS | METH_KEYWORDS, doc_d_13.c_str()},
   {"get_uint64_max", (PyCFunction)c2py::pyfkw<fun_14>, METH_VARARGS | METH_KEYWORDS, doc_d_14.c_str()},
   {"get_ushort_max", (PyCFunction)c2py::pyfkw<fun_15>, METH_VARARGS | METH_KEYWORDS, doc_d_15.c_str()},
   {"identity_int16", (PyCFunction)c2py::pyfkw<fun_16>, METH_VARARGS | METH_KEYWORDS, doc_d_16.c_str()},
   {"identity_int32", (PyCFunction)c2py::pyfkw<fun_17>, METH_VARARGS | METH_KEYWORDS, doc_d_17.c_str()},
   {"identity_int64", (PyCFunction)c2py::pyfkw<fun_18>, METH_VARARGS | METH_KEYWORDS, doc_d_18.c_str()},
   {"identity_longlong", (PyCFunction)c2py::pyfkw<fun_19>, METH_VARARGS | METH_KEYWORDS, doc_d_19.c_str()},
   {"identity_short", (PyCFunction)c2py::pyfkw<fun_20>, METH_VARARGS | METH_KEYWORDS, doc_d_20.c_str()},
   {"identity_size_t", (PyCFunction)c2py::pyfkw<fun_21>, METH_VARARGS | METH_KEYWORDS, doc_d_21.c_str()},
   {"identity_uint16", (PyCFunction)c2py::pyfkw<fun_22>, METH_VARARGS | METH_KEYWORDS, doc_d_22.c_str()},
   {"identity_uint32", (PyCFunction)c2py::pyfkw<fun_23>, METH_VARARGS | METH_KEYWORDS, doc_d_23.c_str()},
   {"identity_uint64", (PyCFunction)c2py::pyfkw<fun_24>, METH_VARARGS | METH_KEYWORDS, doc_d_24.c_str()},
   {"identity_ushort", (PyCFunction)c2py::pyfkw<fun_25>, METH_VARARGS | METH_KEYWORDS, doc_d_25.c_str()},
   {"multiply_int64", (PyCFunction)c2py::pyfkw<fun_26>, METH_VARARGS | METH_KEYWORDS, doc_d_26.c_str()},
   {"identity_int8", (PyCFunction)c2py::pyfkw<fun_27>, METH_VARARGS | METH_KEYWORDS, doc_d_27.c_str()},
   {"identity_uint8", (PyCFunction)c2py::pyfkw<fun_28>, METH_VARARGS | METH_KEYWORDS, doc_d_28.c_str()},
   {"get_int8_min", (PyCFunction)c2py::pyfkw<fun_29>, METH_VARARGS | METH_KEYWORDS, doc_d_29.c_str()},
   {"get_int8_max", (PyCFunction)c2py::pyfkw<fun_30>, METH_VARARGS | METH_KEYWORDS, doc_d_30.c_str()},
   {"get_uint8_max", (PyCFunction)c2py::pyfkw<fun_31>, METH_VARARGS | METH_KEYWORDS, doc_d_31.c_str()},
   {nullptr, nullptr, 0, nullptr} // Sentinel
};

//--------------------- module struct & init error definition ------------

//// module doc directly in the code or "" if not present...
/// Or mandatory ?
static struct PyModuleDef module_def = {PyModuleDef_HEAD_INIT,
                                        "integers",        /* name of module */
                                        R"RAWDOC()RAWDOC", /* module documentation, may be NULL */
                                        -1, /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
                                        module_methods,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL};

//--------------------- module init function -----------------------------

extern "C" __attribute__((visibility("default"))) PyObject *PyInit_integers() {

  if (not c2py::check_python_version("integers")) return NULL;

  // import numpy iff 'numpy/arrayobject.h' included
#ifdef Py_ARRAYOBJECT_H
  import_array();
#endif

  PyObject *m;

  if (PyType_Ready(&c2py::wrap_pytype<c2py::py_range>) < 0) return NULL;

  m = PyModule_Create(&module_def);
  if (m == NULL) return NULL;

  auto &conv_table = *c2py::conv_table_sptr.get();

  conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;

  return m;
}
#endif
// CLAIR_WRAP_GEN
