#pragma once
#include <tuple>

// The user facing part of the c2py library
// i.e. what is used in the c2py_module section of the user file.

// -------------  Annotations for function ---------------

// The attribute are only meaningfull for clang tools, hence for clang.
#ifdef __clang__
#define C2PY_IGNORE __attribute__((annotate("c2py_ignore")))
#define C2PY_WRAP_AS_METHOD __attribute__((annotate("c2py_wrap_as_method")))
#define C2PY_MODULE_INIT __attribute__((annotate("c2py_module_init")))
#define C2PY_NOGIL __attribute__((annotate("c2py_nogil")))
#define C2PY_RENAME(X) __attribute__((annotate("c2py_rename:" #X)))
#else
#define C2PY_IGNORE
#define C2PY_WRAP_AS_METHOD
#define C2PY_MODULE_INIT
#define C2PY_NOGIL
#define C2PY_RENAME(X)
#endif

//#define C2PY_METHODS_AS_PROPERTY __attribute__((annotate("c2py_methods_as_property")))

// ---------   Traits to be specialized in c2py_module ----------
namespace c2py_module {
  template <typename T> struct add_methods_to {};
} // namespace c2py_module

namespace c2py {

  // ----------  c2py::dispatch to declare a specific dispatch -------------

  template <auto... a> struct dispatch_t {
    static constexpr auto value = std::tuple{a...};
  };
  template <auto... a> constexpr dispatch_t<a...> dispatch = {};

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
  //template <typename T> C2PY_WRAP_AS_METHOD static T clone(T const &x) { return T{x}; };

  // ----------- API for arithmetic operations ---------------------------

  // FIXME : extend for other operations
  // Name of operations
  enum class OpName { Add, Sub, Mul, Div };

  // The user specialize this struct for type T and operation Op
  template <typename T, OpName Op> struct arithmetic;

} // namespace c2py
