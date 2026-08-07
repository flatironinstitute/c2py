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
  ARITH_OP(LShift, <<);
  ARITH_OP(IAdd, +=);
  ARITH_OP(ISub, -=);
  ARITH_OP(IMul, *=);
  ARITH_OP(IDiv, /=);

#undef ARITH_OP

  // Unary minus: separate specialization (single argument)
  template <> struct arith_op<OpName::Neg> {
    static auto invoke(auto &&x) { return -x; }
  };

  template <OpName Op, typename T1, typename T2, bool InPlace = false> bool tp_arithmetic_impl1(PyObject *&r, PyObject *a1, PyObject *a2) {
    using conv1 = py_converter<T1>;
    using conv2 = py_converter<T2>;
    bool ok     = conv1::is_convertible(a1, false) and conv2::is_convertible(a2, false);
    if (ok) {
      try {
        if constexpr (InPlace) {
          arith_op<Op>::invoke(conv1::py2c(a1), conv2::py2c(a2));
          Py_INCREF(a1);
          r = a1;
        } else {
          r = cxx2py(arith_op<Op>::invoke(conv1::py2c(a1), conv2::py2c(a2)));
        }
      } catch (std::exception const &e) {
        auto err = std::string(".. Error in arithmetic operation  : \n") + e.what();
        PyErr_SetString(PyExc_RuntimeError, err.c_str());
      }
    }
    return ok;
  }

  template <typename T, OpName Op, bool InPlace = false> PyObject *tp_arithmetic_impl2(PyObject *a1, PyObject *a2) {
    return [&a1, &a2]<typename... P>(std::tuple<P...> *) {
      PyObject *r = nullptr;
      if ((tp_arithmetic_impl1<Op, typename P::first_type, typename P::second_type, InPlace>(r, a1, a2) or ...))
        return r;
      else {
        Py_INCREF(Py_NotImplemented);
        return Py_NotImplemented;
      }
    }(static_cast<arithmetic<T, Op> *>(nullptr));
  }

  template <typename T, OpName Op, bool InPlace = false>
  static constexpr binaryfunc tp_number_impl = []() {
    if constexpr (arithmetic_is_specialized<T, Op>)
      return &tp_arithmetic_impl2<T, Op, InPlace>;
    else
      return (binaryfunc) nullptr;
  }();

  // ---- Unary dispatch (unaryfunc: single PyObject* arg) ----

  template <OpName Op, typename T> PyObject *tp_unary_impl(PyObject *a) {
    try {
      return cxx2py(arith_op<Op>::invoke(py_converter<T>::py2c(a)));
    } catch (std::exception const &e) {
      auto err = std::string(".. Error in unary arithmetic operation  : \n") + e.what();
      PyErr_SetString(PyExc_RuntimeError, err.c_str());
      return nullptr;
    }
  }

  template <typename T, OpName Op>
  static constexpr unaryfunc tp_unary_number_impl = []() {
    if constexpr (arithmetic_is_specialized<T, Op>)
      return &tp_unary_impl<Op, T>;
    else
      return (unaryfunc) nullptr;
  }();

  template <typename T>
  // NOLINTNEXTLINE
  static PyNumberMethods tp_as_number_impl = {
     tp_number_impl<T, OpName::Add>,                //     binaryfunc nb_add;
     tp_number_impl<T, OpName::Sub>,                //     binaryfunc nb_subtract;
     tp_number_impl<T, OpName::Mul>,                //     binaryfunc nb_multiply;
     0,                                             //     binaryfunc nb_remainder;
     0,                                             //     binaryfunc nb_divmod;
     0,                                             //     ternaryfunc nb_power;
     tp_unary_number_impl<T, OpName::Neg>,          //     unaryfunc nb_negative;
     0,                                             //     unaryfunc nb_positive;
     0,                                             //     unaryfunc nb_absolute;
     0,                                             //     inquiry nb_bool;
     0,                                             //     unaryfunc nb_invert;
     tp_number_impl<T, OpName::LShift, true>,        //     binaryfunc nb_lshift;
     0,                                             //     binaryfunc nb_rshift;
     0,                                             //     binaryfunc nb_and;
     0,                                             //     binaryfunc nb_xor;
     0,                                             //     binaryfunc nb_or;
     0,                                             //     unaryfunc nb_int;
     0,                                             //     void *nb_reserved;
     0,                                             //     unaryfunc nb_float;

     tp_number_impl<T, OpName::IAdd, true>,         //     binaryfunc nb_inplace_add;
     tp_number_impl<T, OpName::ISub, true>,         //     binaryfunc nb_inplace_subtract;
     tp_number_impl<T, OpName::IMul, true>,         //     binaryfunc nb_inplace_multiply;
     0,                                             //     binaryfunc nb_inplace_remainder;
     0,                                             //     ternaryfunc nb_inplace_power;
     0,                                             //     binaryfunc nb_inplace_lshift;
     0,                                             //     binaryfunc nb_inplace_rshift;
     0,                                             //     binaryfunc nb_inplace_and;
     0,                                             //     binaryfunc nb_inplace_xor;
     0,                                             //     binaryfunc nb_inplace_or;

     0,                                             //     binaryfunc nb_floor_divide;
     tp_number_impl<T, OpName::Div>,                //     binaryfunc nb_true_divide;
     0,                                             //     binaryfunc nb_inplace_floor_divide;
     tp_number_impl<T, OpName::IDiv, true>,         //     binaryfunc nb_inplace_true_divide;

     0,                                             //     unaryfunc nb_index;

     0,                                             //     binaryfunc nb_matrix_multiply;
     0,                                             //     binaryfunc nb_inplace_matrix_multiply;
  };

  // tp_as_number
  template <typename T>
  // NOLINTNEXTLINE
  static constexpr PyNumberMethods *tp_as_number = []() {
    if constexpr (has_any_arithmetic<T>)
      return &c2py::tp_as_number_impl<T>;
    else
      return (PyNumberMethods *)nullptr;
  }();

} // namespace c2py
