#pragma once
#include "pytypes/wrap.hpp"
#include "./py_converter.hpp"
#include "converters/wrapped.hpp"
namespace c2py {

  /// RangeOfConvertibles
  namespace concepts {

    // FIXME : remove in c++23
    auto _copy(auto x) { return x; } //

    template <typename T>
    concept RangeOfConvertibles = std::ranges::range<T> and requires(T x) {
      // FIXME C++23
      //  { auto{*std::begin(x)} } -> IsConvertible;
      { _copy(*std::begin(x)) } -> IsConvertible;
    };
  } // namespace concepts
  // *********************************************
  //                py_range
  // Eraser for RangeOfConvertibles, erasing
  // values into PyObject *
  // *********************************************
  struct py_range {
    std::function<PyObject *(PyObject *)> lazy_iter;

    py_range()                            = delete;
    py_range(py_range const &)            = delete;
    py_range(py_range &&)                 = default;
    py_range &operator=(py_range const &) = delete;
    py_range &operator=(py_range &&)      = delete;
    ~py_range()                           = default;

    template <typename T>
      requires(concepts::RangeOfConvertibles<std::decay_t<T>>)
    py_range(T &&x)
       : lazy_iter{[y = std::make_shared<std::decay_t<T>>(std::forward<T>(x))](PyObject *self) mutable -> PyObject * {
           // We need the shared ptr as lambda in std::function MUST be copyable
           // and T may not be copyable... (e.g. a coroutine)
           return make_iterator(y->begin(), y->end(), self);
         }} {}
  };

  // ------------- We wrap py_range --------------

  template <> inline constexpr bool is_wrapped<py_range>     = true;
  template <> inline constexpr auto tp_name<py_range>        = "c2py_range";
  template <> inline constexpr getiterfunc tp_iter<py_range> = [](PyObject *self) -> PyObject * { return py2cxx<py_range>(self).lazy_iter(self); };

  // -----  a converter into a py_range -----

  struct py_converter_to_py_range {
    template <typename U> static PyObject *c2py(U &&x) { return py_converter<py_range>::c2py(py_range{std::forward<U>(x)}); }
    static void py2c(PyObject *ob)                                 = delete;
    static bool is_convertible(PyObject *ob, bool raise_exception) = delete;
  };

  template <typename T>
    requires(concepts::RangeOfConvertibles<T> and not is_wrapped<T> and not concepts::IsConvertibleCPP2Py_backwd<std::decay_t<T>>)
  struct py_converter<T> : py_converter_to_py_range {}; //

} // namespace c2py
