#pragma once
#include <vector>
#include <any>
#include <algorithm>
#include "../pytypes/wrap.hpp"

namespace c2py {

  template <typename R, typename... T> static inline const std::string simple_signature = (cpp_name<T> + ... + "") + " -> " + cpp_name<R>;

  // -------------------  pycfun23--------------------

  class pycfun23 {
    std::string const *sig;
    using conv_f_t = bool (*)(PyObject *, bool);
    std::vector<conv_f_t> c_args;
    virtual PyObject *call(PyObject *x, PyObject *y, PyObject *z) const = 0;

    protected:
    pycfun23(std::vector<conv_f_t> &&cargs, std::string const *sig) : sig{sig}, c_args(std::move(cargs)) {}

    public:
    virtual ~pycfun23() = default;

    pycfun23(pycfun23 const &)            = default;
    pycfun23(pycfun23 &&)                 = default;
    pycfun23 &operator=(pycfun23 const &) = default;
    pycfun23 &operator=(pycfun23 &&)      = default;

    [[nodiscard]] std::string const &signature() const { return *sig; }

    bool is_callable(PyObject *x, PyObject *y, PyObject *z, bool raise_exception = false) const noexcept {
      bool b = (z == nullptr ? true : (*c_args[2])(y, raise_exception));
      return b and (*c_args[0])(x, raise_exception) and (*c_args[1])(y, raise_exception);
    }

    PyObject *operator()(PyObject *x, PyObject *y, PyObject *z) const {
      try {
        return call(x, y, z);
      }
      // FIXME : catch keyboard and std::exception only
      catch (std::exception const &e) {
        auto err = std::string(".. Error  : \n") + e.what();
        PyErr_SetString(PyExc_RuntimeError, err.c_str());
      }
      return nullptr; // avoid warning
    }
  };

  // ------------

  template <typename R, typename... T> class pycfun23_impl : public pycfun23 {
    using fnt_ptr_t = R (*)(T...);
    fnt_ptr_t f;

    public:
    pycfun23_impl(fnt_ptr_t f) : pycfun23{{&py_converter<std::decay_t<T>>::is_convertible...}, &simple_signature<R, T...>}, f{f} {}

    PyObject *call(PyObject *x, PyObject *y, PyObject *z) const override {
      auto l = [ff = this->f]<typename Tu, size_t... Is>(std::index_sequence<Is...>, Tu &&tu) {
        if constexpr (std::is_same_v<void, R>) {
          ff(py2cxx<T>(std::get<Is>(tu))...);
          Py_RETURN_NONE;
        } else
          return cxx2py(ff(py2cxx<T>(std::get<Is>(tu))...));
      };
      using seq_t = std::make_index_sequence<sizeof...(T)>;
      if constexpr (sizeof...(T) == 2)
        return l(seq_t{}, std::tie(x, y));
      else
        return l(seq_t{}, std::tie(x, y, z));
    }
  };

  // ------------

  //template <typename Cls, bool is_const, typename R, typename ...T> class pycmeth23_impl : public pycfun23 {
  //using fnt_ptr_t = std::conditional_t<is_const, R (Cls::*)(T...) const, R (Cls::*)(T...)>;
  //fnt_ptr_t f;
  //public:

  //pycmeth23_impl(fnt_ptr_t f) : pycfun23 {{&py_converter<std::decay_t<Cls>>::is_convertible, &py_converter<std::decay_t<T>>::is_convertible...},  &simple_signature<R, Cls, T...>}, f{f}  {}

  //virtual PyObject* call (PyObject *self, PyObject *x, PyObject*y) const override {
  //auto l       = [&self, f= this->f]<typename Tu, size_t... Is>(std::index_sequence<Is...>, Tu &&tu) {
  //return cxx2py((py2c<Cls>(self).*f)(py2cxx<T>(std::get<Is>(tu))...));
  //};
  //using seq_t= std::make_index_sequence<sizeof...(T)>;
  //if constexpr (sizeof...(T)==2) return l(seq_t{}, std::tie(x));
  //else return l(seq_t{}, std::tie(x,y));
  //}
  //};

  // ------------

  template <typename R, typename... T> std::unique_ptr<pycfun23> cfun2(R (*f)(T...)) { return std::make_unique<pycfun23_impl<R, T...>>(f); }

  //template <typename Cls, typename R, typename... T>
  //std::unique_ptr<pycfun23> cfun2(R (Cls::*f)(T...)) {
  //return std::make_unique<pycmeth23_impl<Cls, false, R, T...>>(f);
  //}

  //template <typename Cls, typename R, typename... T>
  //std::unique_ptr<pycfun23> cfun2(R (Cls::*f)(T...) const) {
  //return std::make_unique<pycmeth23_impl<Cls, true, R, T...>>(f);
  /*}*/
  //template <typename Lambda> auto cfun2(Lambda) {
  //  return cfun2(&std::decay_t<Lambda>::operator());
  //}

} // namespace c2py
