#pragma once
//#include <stdexcept>
#include "./cpp_name.hpp"
#include "./pyref.hpp"
#include "./py_converter.hpp"
#include "./util/nv_pair.hpp"
#include "./util/macros.hpp"
#include <stdexcept>

namespace c2py {

  namespace detail {

    // Convert x to python. If x is not convertible and is a lambda or alike
    // we make an attempt a std::function out of it.
    template <typename T> static PyObject *cxx2py_or_fun(T &&x) {
      if constexpr (concepts::IsConvertibleC2Py<std::decay_t<T>>)
        return py_converter<std::decay_t<T>>::c2py(std::forward<T>(x));
      else
        return c2py::cxx2py(std::function{std::forward<T>(x)}); // FIXME : a better error message with static_assert(false)
    }

    template <typename A> static constexpr int is_nv_pair             = 0;
    template <typename A> static constexpr int is_nv_pair<nv_pair<A>> = 1;

    // To separate the positional from the kw arguments, passed as nv_pair
    struct erased_arguments_t {
      pyref args, kwargs;
      int args_current_pos = 0;
      // construct with the proper tuple size !
      erased_arguments_t(int n_args) {
        args   = PyTuple_New(n_args);
        kwargs = PyDict_New();
      }

      void operator()(auto const &x) {
        [[maybe_unused]] int status = PyTuple_SetItem(args, args_current_pos++, detail::cxx2py_or_fun(x));
        assert(status == 0);
      }

      template <typename A> void operator()(nv_pair<A> const &x) {
        [[maybe_unused]] int status = PyDict_SetItemString(kwargs, x.name.c_str(), detail::cxx2py_or_fun(x.value));
        assert(status == 0);
      }
    };

    std::string format_error(pyref const &r, std::string const &fname, std::string const &cpp_name_R, std::string const &converter_error);

  } // namespace detail

  template <typename R = pyref> struct pyfunction : pyref {
    std::string fname;

    private:
    // split the function name A.B.f into A.B , f
    // if no ., then __main__, f
    std::pair<std::string, std::string> split_fname(std::string const &s) {
      if (auto pos = s.find_last_of('.'); pos == std::string::npos)
        return {"__main__", s};
      else
        return {s.substr(0, pos), s.substr(pos + 1, std::string::npos)};
    }

    public:
    pyfunction(std::string const &module_name, std::string const &fname)
       : pyref{pyref::get_class(module_name.c_str(), fname.c_str(), true)}, fname{fname} {
      if (PyErr_Occurred()) { throw std::runtime_error{get_python_error()}; }
    }

    pyfunction(std::string const &qualifiedname) {
      auto [module_name, fnt_name] = split_fname(qualifiedname);
      static_cast<pyref &>(*this)  = pyref::get_class(module_name.data(), fnt_name.data(), true);
      this->fname                  = fnt_name;
      if (PyErr_Occurred()) { throw std::runtime_error{get_python_error()}; }
    }

    //pyfunction(pyref x) : pyref{std::move(x)} {}
    //pyfunction(PyObject *ob) : pyfunction{pyref::borrowed(ob)} {}

    ~pyfunction()                             = default;
    pyfunction(pyfunction const &)            = default;
    pyfunction(pyfunction &&)                 = default;
    pyfunction &operator=(pyfunction const &) = default;
    pyfunction &operator=(pyfunction &&)      = default;

    template <typename... T> R operator()(T const &...x) const {
      if (this->is_null()) throw std::runtime_error{"Empty function"};
      // x -> python mais si x nv_pair -> add in dict.
      // if one T is a nv_pair -> separate args, pydict into a tuple and a dict
      // 2 overload -> T and nv_pair<T> , pass and fold.
      if (is_null()) throw std::runtime_error{"Calling null function"};

      static constexpr int n_kwargs = (detail::is_nv_pair<T> + ... + 0);
      static constexpr int n_args   = sizeof...(T) - n_kwargs;
      pyref r;
      if constexpr (n_kwargs > 0) {
        auto erased_args = detail::erased_arguments_t{n_args};
        (erased_args(x), ...);
        r = PyObject_Call(this->ob, erased_args.args, erased_args.kwargs);
      } else
        r = PyObject_CallFunctionObjArgs(this->ob, detail::cxx2py_or_fun(x)..., NULL);
      if (r.is_null()) {
        PyErr_Print();
        throw std::runtime_error{"Error calling the function " + fname}; //+ get_python_error()};
      }
      if (not py_converter<R>::is_convertible(r, true)) {
        auto err = get_python_error(); // clean error
        throw std::runtime_error{detail::format_error(r, fname, cpp_name<R>, err)};
      }
      return py2cxx<R>(r);
    }
  };
} // namespace c2py