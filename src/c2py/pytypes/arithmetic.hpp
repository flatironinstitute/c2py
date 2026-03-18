#pragma once
#include <tuple>
#include "../user_api.hpp"
#include "../py_converter.hpp"
namespace c2py {

  // ----- Implement all operations as generic

  template <OpName Op> struct arith_op;

/// NOLINTNEXTLINE
#define ARITH_OP(Opname, Op)                                                                                                                         \
  template <> struct arith_op<OpName::Opname> {                                                                                                      \
    static auto invoke(auto &&x, auto &&y) { return x Op y; }                                                                                        \
  };
  ARITH_OP(Add, +);
  ARITH_OP(Sub, -);
  ARITH_OP(Mul, *);
  ARITH_OP(Div, /);

#undef ARITH_OP

  template <OpName Op, typename T1, typename T2> static bool tp_arithmetic_impl1(PyObject *&r, PyObject *a1, PyObject *a2) {
    using conv1 = py_converter<T1>;
    using conv2 = py_converter<T2>;
    bool ok     = conv1::is_convertible(a1, false) and conv2::is_convertible(a2, false);
    if (ok) {
      try {
        r = cxx2py(arith_op<Op>::invoke(conv1::py2c(a1), conv2::py2c(a2)));
      } catch (std::exception const &e) {
        auto err = std::string(".. Error in arithmetic operation  : \n") + e.what();
        PyErr_SetString(PyExc_RuntimeError, err.c_str());
      }
    }
    return ok;
  }

  template <typename T, OpName Op> static PyObject *tp_arithmetic_impl2(PyObject *a1, PyObject *a2) {
    return [&a1, &a2]<typename... P>(std::tuple<P...>) {
      PyObject *r = nullptr;
      if ((tp_arithmetic_impl1<Op, typename P::first_type, typename P::second_type>(r, a1, a2) or ...))
        return r;
      else {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
      }
    }(arithmetic<T, Op>{});
  }

  template <typename T, OpName Op>
  static constexpr binaryfunc tp_number_impl = []() {
    if constexpr (requires { std::get<0>(arithmetic<T, Op>{}); })
      return &tp_arithmetic_impl2<T, Op>;
    else
      return (binaryfunc) nullptr;
  }();

  template <typename T>
  // NOLINTNEXTLINE
  static PyNumberMethods tp_as_number_impl = {
     tp_number_impl<T, OpName::Add>, //     binaryfunc nb_add;
     tp_number_impl<T, OpName::Sub>, //     binaryfunc nb_subtract;
     tp_number_impl<T, OpName::Mul>, //     binaryfunc nb_multiply;
     0,                              //     binaryfunc nb_remainder;
     0,                              //     binaryfunc nb_divmod;
     0,                              //     ternaryfunc nb_power;
     0,                              //     unaryfunc nb_negative;
     0,                              //     unaryfunc nb_positive;
     0,                              //     unaryfunc nb_absolute;
     0,                              //     inquiry nb_bool;
     0,                              //     unaryfunc nb_invert;
     0,                              //     binaryfunc nb_lshift;
     0,                              //     binaryfunc nb_rshift;
     0,                              //     binaryfunc nb_and;
     0,                              //     binaryfunc nb_xor;
     0,                              //     binaryfunc nb_or;
     0,                              //     unaryfunc nb_int;
     0,                              //     void *nb_reserved;
     0,                              //     unaryfunc nb_float;

     0, //     binaryfunc nb_inplace_add;
     0, //     binaryfunc nb_inplace_subtract;
     0, //     binaryfunc nb_inplace_multiply;
     0, //     binaryfunc nb_inplace_remainder;
     0, //     ternaryfunc nb_inplace_power;
     0, //     binaryfunc nb_inplace_lshift;
     0, //     binaryfunc nb_inplace_rshift;
     0, //     binaryfunc nb_inplace_and;
     0, //     binaryfunc nb_inplace_xor;
     0, //     binaryfunc nb_inplace_or;

     0, //     binaryfunc nb_floor_divide;
     tp_number_impl<T, OpName::Div>, //     binaryfunc nb_true_divide;
     0, //     binaryfunc nb_inplace_floor_divide;
     0, //     binaryfunc nb_inplace_true_divide;

     0, //     unaryfunc nb_index;

     0, //     binaryfunc nb_matrix_multiply;
     0, //     binaryfunc nb_inplace_matrix_multiply;
  };

  // FIXME : relies on Add always defined
  template <typename T> constexpr auto _arith_defined() -> decltype(arithmetic<T, OpName::Add>{}) { return arithmetic<T, OpName::Add>{}; }

  // tp_as_number
  template <typename T>
  // NOLINTNEXTLINE
  static constexpr PyNumberMethods *tp_as_number = []() {
    if constexpr (requires { _arith_defined<T>(); })
      return &c2py::tp_as_number_impl<T>;
    else
      return (PyNumberMethods *)nullptr;
  }();

} // namespace c2py
