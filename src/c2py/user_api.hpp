#pragma once

// The user facing part of the c2py library
// i.e. what is used in the c2py_module section of the user file.

// -------------  Annotations for function ---------------

#define C2PY_IGNORE __attribute__((annotate("c2py_ignore")))
#define C2PY_WRAP __attribute__((annotate("c2py_wrap")))
#define C2PY_NOGIL __attribute__((annotate("c2py_nogil")))

//#define C2PY_METHODS_AS_PROPERTY __attribute__((annotate("c2py_methods_as_property")))

// ---------   Traits to be specialized in c2py_module ----------
namespace c2py_module {
  template <typename T> struct add_methods_to {};
} // namespace c2py_module

namespace c2py {

  // ----------  c2py::dispatch to declare a specific dispatch -------------

  template <auto... T> struct dispatch_t {};
  template <auto... T> constexpr dispatch_t<T...> dispatch = {};

  // ----------- Some cast operator for the user ---------------------------
  // when f is overloaded, cast<arguments....>(f) will disambiguite it
  // simpler than the plain static_cast (which requires the return type R,
  // and possibly the class C for a method, while the compiler can deduce them)
  //
  template <typename... A> static constexpr auto cast   = []<typename R>(R (*f)(A...)) { return f; };
  template <typename... A> static constexpr auto castm  = []<typename R, typename C>(R (C::*f)(A...)) { return f; };
  template <typename... A> static constexpr auto castmc = []<typename R, typename C>(R (C::*f)(A...) const) { return f; };

  /// A clone function. c2py::clone<T> is a clone function
  /// Cf example, it allows to add a clone function method to a class.
  template <typename T> static T clone(T const &x) { return T{x}; };

  // ----------- API for arithmetic operations ---------------------------

  // FIXME : extend for other operations
  // Name of operations
  enum class OpName { Add, Sub, Mul, Div };

  // The user specialize this struct for type T and operation Op
  template <typename T, OpName Op> struct arithmetic;

} // namespace c2py
