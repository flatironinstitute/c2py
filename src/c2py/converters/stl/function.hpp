#include <functional>
#include "./common.hpp"
#include "../../dyn_dispatch/dispatcher.hpp"

namespace c2py {

  // Converter for std::function
  // We just enable the tp_call and tp_name
  // and wrap<std::function<...>> is a wrapped callable object
  // The converter will :
  // c2py : allocate the wrapped object
  // py2c : make a lambda in c++ that wraps the python function

  namespace detail {

    template <typename T> constexpr const char *empty_string = "";

    // a dispatcher for this std::function
    template <typename R, typename... T>
    static const auto std_function_call = dispatcher_f_kw_t{cfun(&std::function<R(T...)>::operator(), empty_string<T>...)};

  } // namespace detail

  // The call operator for std::function wrapped in python
  template <typename R, typename... T> constexpr ternaryfunc tp_call<std::function<R(T...)>> = pyfkw<detail::std_function_call<R, T...>>;

  // Its name
  // FIXME : improve the signature when std::string is constexpr in libc++ [wait for implementation in clang]
  template <typename R, typename... T> constexpr const char *tp_name<std::function<R(T...)>> = "Callable";

  // The converter
  template <typename R, typename... T>

  struct py_converter<std::function<R(T...)>> {
    static_assert(concepts::IsConvertibleC2Py<R>, "Return type not convertible");
    static_assert((concepts::IsConvertiblePy2C<T> and ... and true), "Parameter not convertible");

    using c_t  = std::function<R(T...)>;
    using py_t = wrap<c_t>;

    static bool is_pytype_ready() {
      static bool ready = false;
      if (not ready) {
        if (PyType_Ready(&wrap_pytype<c_t>) < 0) return false;
        ready = true;
      }
      return true;
    }

    template <typename U> static PyObject *c2py(U &&x) {
      // allocate the object, as default py_converter of a wrapped object.
      if (not is_pytype_ready()) return nullptr;
      py_t *self = (py_t *)wrap_pytype<c_t>.tp_alloc(&wrap_pytype<c_t>, 0);
      if (self != nullptr) { self->_c = new c_t{std::forward<U>(x)}; } // NOLINT
      return (PyObject *)self;
    }

    // any callable will be ok here. We can't check at this stage
    // whether the python function will accept our arguments...
    static bool is_convertible(PyObject *ob, bool raise_exception) {
      if (PyCallable_Check(ob)) return true;
      if (raise_exception) {
        PyErr_SetString(PyExc_TypeError, ("Cannot convert "s + to_string(ob) + " std::function as it is not callable"s).c_str());
      }
      return false;
    }

    //
    static c_t py2c(PyObject *ob) {
      if (not is_pytype_ready()) return nullptr;
      // If we convert a wrapped std::function, just extract it.
      if (PyObject_TypeCheck(ob, &wrap_pytype<c_t>)) { return *(((py_t *)ob)->_c); }
      // otherwise, we build a new std::function around the python function
      pyref py_fnt = pyref::borrowed(ob);
      auto l       = [py_fnt](T... x) mutable -> R { // py_fnt is a pyref, it will keep the ref and manage the ref counting...
        pyref ret = PyObject_CallFunctionObjArgs(py_fnt, (PyObject *)pyref{cxx2py(x)}..., nullptr);
        if (ret.is_null()) throw exception_raised_in_python{};
        if (not py_converter<R>::is_convertible(ret, false))
          throw std::runtime_error{"\n Cannot convert function result " + to_string(ret) + " from python to C++"};
        return py_converter<R>::py2c(ret);
      };
      return l;
    }
  };

} // namespace c2py
