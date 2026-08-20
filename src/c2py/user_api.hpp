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
#define C2PY_PROPERTY_GET(X) __attribute__((annotate("c2py_property_get:" #X)))
#define C2PY_PROPERTY_SET(X) __attribute__((annotate("c2py_property_set:" #X)))
#define C2PY_DEPRECATED_PARAMETER_NAME(...) __attribute__((annotate("c2py_deprecated_params:" C2PY_AS_STRING(__VA_ARGS__))))
#else
#define C2PY_IGNORE
#define C2PY_WRAP_AS_METHOD
#define C2PY_MODULE_INIT
#define C2PY_NOGIL
#define C2PY_RENAME(X)
#define C2PY_PROPERTY_GET(X)
#define C2PY_PROPERTY_SET(X)
#define C2PY_DEPRECATED_PARAMETER_NAME(...)
#endif

#define C2PY_AS_STRING(...) C2PY_AS_STRING2(__VA_ARGS__)
#define C2PY_AS_STRING2(...) #__VA_ARGS__

#define C2PY_ANNOTATE(X) __attribute__((annotate(X)))
#define C2PY_GUARD(X) C2PY_ANNOTATE(AS_STRING2(c2py_guard_##X))

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

  // ----------- Opt-in for repr based serialization -----------------------

  // The class's operator<< must emit valid Python that evaluates back to an equal object,
  // in the module the class is wrapped in.
  template <typename T> constexpr bool serialize_via_repr = false;

  // ----------- API for arithmetic operations ---------------------------

  // Name of operations
  enum class OpName { Add, Sub, Mul, Div, LShift, Neg, IAdd, ISub, IMul, IDiv };

  // The user specializes this struct for type T and operation Op.
  // Specializations inherit from std::tuple<std::pair<T1,T2>, ...>.
  // The primary template is defined (empty) so that is_specialized detection works
  // without requiring default-constructibility of the wrapped types.
  template <typename T, OpName Op> struct arithmetic {};

  // Detect whether arithmetic<T, Op> has been specialized (i.e. inherits from a non-empty tuple)
  template <typename T, OpName Op>
  concept arithmetic_is_specialized = !std::is_empty_v<arithmetic<T, Op>>;

  // Detect whether T has any arithmetic operator specialized
  template <typename T>
  concept has_any_arithmetic = arithmetic_is_specialized<T, OpName::Add> or arithmetic_is_specialized<T, OpName::Sub>
                               or arithmetic_is_specialized<T, OpName::Mul> or arithmetic_is_specialized<T, OpName::Div>
                               or arithmetic_is_specialized<T, OpName::LShift> or arithmetic_is_specialized<T, OpName::Neg>
                               or arithmetic_is_specialized<T, OpName::IAdd> or arithmetic_is_specialized<T, OpName::ISub>
                               or arithmetic_is_specialized<T, OpName::IMul> or arithmetic_is_specialized<T, OpName::IDiv>;

} // namespace c2py

// ----------- PyMethodDef row helper -------------------------------------------
// Used by clair-generated `.wrap.cxx` files to write one method/function-table
// row instead of the long form
//   {name, (PyCFunction)c2py::pyfkw<_c2py_fun_<h>>, METH_VARARGS | METH_KEYWORDS, _c2py_doc_<h>.c_str()}
//
// Usage:
//   PMDF("py_name", hash)               -> regular row
//   PMDF("py_name", hash, METH_STATIC)  -> extra flags OR'd in (e.g. static methods)
//
// Expects two identifiers to be in scope:
//   _c2py_fun_<hash>   : the dispatcher  (used via c2py::pyfkw<...>)
//   _c2py_doc_<hash>   : the doc string  (a std::string, .c_str() called on it)
#define PMDF(name, hash, ...)                                                                                                                          \
  { name, (PyCFunction)c2py::pyfkw<_c2py_fun_##hash>, METH_VARARGS | METH_KEYWORDS __VA_OPT__(|) __VA_ARGS__, _c2py_doc_##hash.c_str() }
