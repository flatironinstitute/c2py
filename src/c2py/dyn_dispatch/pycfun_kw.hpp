#pragma once
#include <type_traits>
#include <vector>
#include <any>
#include <algorithm>
#include "../util/nv_pair.hpp"
#include "../pytypes/wrap.hpp"

namespace c2py {

  // ====================== a specific exception ============
  // A C++ exception raised when a Python function called by C++
  // has raised an exception
  struct exception_raised_in_python {};

  // =====================  argument_t ===========================

  // Handle one argument of a dynamically dispatched function pycfun_kw
  // Erase the C++ type and convertible call
  // We need a set of erased argument to determine which function to call
  struct argument_t {
    std::string name;                  // name of the argument. Can be empty
    std::string const *type_name;      // Name of the C++ type for error. FIXME : Python AND C++ names?
    bool (*is_conv)(PyObject *, bool); // eraser of py_converter<T>::is_convertible
    std::any default_value;            // the value. Can be none.

    [[nodiscard]] bool has_default() const { return default_value.has_value(); }

    // Can the object x be converted into the type of the argument ?
    // raise_exception : as in converters. Will raise Python exceptions if true.
    bool is_convertible(PyObject *x, bool raise_exception) const { return (*is_conv)(x, raise_exception); }
  };

  // Two makers for argument_t
  // Can not use constructor because it is explicitely called with <A>
  // First one for argument without a default value.
  template <typename A> auto make_argument(std::string const &name) {
    return argument_t{name,
                      &cpp_name<A>,
                      [](PyObject *ob, bool re) -> bool { return py_converter<std::decay_t<A>>::is_convertible(ob, re); },
                      // &py_converter<std::decay_t<A>>::is_convertible, // I use a lambda as in some cases, is_convertible
                      // can have optional parameters (e.g. nda::array_view), so the cast of the pointer does not compile
                      {}};
  }
  // Second one with for an argument with a default value.
  template <typename A, typename T> auto make_argument(nv_pair<T> &&nvp) {
    return argument_t{std::move(nvp).name, &cpp_name<A>,
                      [](PyObject *ob, bool re) -> bool { return py_converter<std::decay_t<A>>::is_convertible(ob, re); },
                      A{std::move(nvp).value}}; //ensure the default_value is an A, whatever T is.
  }

  // =========================== pycfun_kw =====================

  // Abstract class for the eraser for a C++ function into a python function
  class pycfun_kw {
    bool release_GIL = false;            // Not used
    std::vector<argument_t> c_arguments; // arguments of the function, with erased type
    std::string const *rtype_name;       // name of the return type for error messages

    protected:
    // Call the function from args, kwargs
    // Each implementation convert args, kwargs to C++ object, call the function/method, ...
    // and converts back.
    virtual PyObject *call(PyObject *self, PyObject *args, PyObject *kwargs) const = 0;

    public:
    // Calls call method, and takes care of the exceptions, GIL.
    PyObject *operator()(PyObject *self, PyObject *args, PyObject *kwargs) const;

    protected:
    // Constructs by simply moving in the data
    pycfun_kw(std::vector<argument_t> &&c_arguments, std::string const *rtype_name = {})
       : c_arguments{std::move(c_arguments)}, rtype_name{rtype_name} {}

    pycfun_kw(pycfun_kw const &)            = default;
    pycfun_kw(pycfun_kw &&)                 = default;
    pycfun_kw &operator=(pycfun_kw const &) = default;
    pycfun_kw &operator=(pycfun_kw &&)      = default;

    private:
    // Impl detail of arg_cast. Not a lambda, as it does not depend on a T.
    // pos: position of the argument
    // returns
    //   -  args[pos] if pos < size of args else
    //   -  kwargs[ c_arguments[pos].name ]
    PyObject *get_pyarg(int pos, PyObject *args, PyObject *kwargs) const {
      long n_arg_pos_py = (args == nullptr ? 0 : long(PySequence_Size(args)));
      if (pos < n_arg_pos_py)
        return PyTuple_GetItem(args, pos);
      else
        return kwargs ? PyDict_GetItemString(kwargs, c_arguments[pos].name.c_str()) : nullptr;
      //  PyMapping_GetItemString => new ref, while PyDict_GetItemString is a borrowed
      //  PySequence_ITEM => new ref. vs PyTuple_GetItem
    }

    protected:
    // FIXME : n_arg_positional_py should be passed here too

    // Convert the 'pos' argument into C++.
    // by taking it from the arg list args, or from the dictionnary.
    // if T is non-const &, simply convert, no default if possible.
    // else return T or T const & like the converter does
    //
    template <typename T> decltype(auto) arg_cast(int pos, PyObject *args, PyObject *kwargs) const {
      using conv_t = py_converter<std::decay_t<T>>;
      PyObject *p  = get_pyarg(pos, args, kwargs);
      if constexpr (std::is_reference_v<T> and not std::is_const_v<T>) {
        return conv_t::py2c(p);
      } else {
        using conv_r_t = decltype(conv_t::py2c(p));
        static_assert(std::is_same_v<std::decay_t<conv_r_t>, T>);
        using r_t = std::conditional_t<std::is_reference_v<conv_r_t>, T const &, T>;
        // ensure return type if the same in both branch, as fixed by the converter.
        if (p != nullptr)
          return static_cast<r_t>(conv_t::py2c(p));
        else
          return std::any_cast<r_t>(c_arguments[pos].default_value);
      }
    }
    // ------------------

    public:
    virtual ~pycfun_kw() = default;

    // True iif the python arguments can be converted to the c++ arguments
    // raise_exception : should the py_converter raise python exception or fail silently
    // self is ignored
    bool is_callable(PyObject *self, PyObject *args, PyObject *kwargs, bool raise_exception = false) const noexcept;

    // calling signature of the form (x : type, y : type) -> type
    [[nodiscard]] std::string signature() const;
  };

  // ==========  Implementations of pycfun_kw for functions, methods, ....

  // ------------------  C function ---------------------
  // implement pycfunction for a simple function
  template <typename R, typename... T> class c_function_impl_t : public pycfun_kw {
    using fnt_ptr_t = R (*)(T...);
    fnt_ptr_t f;

    public:
    // Note that U can be some pair of a DIFFERENT type than A::type, e.g. double x = 0 ...
    // As long as we can construc the A, it is fine
    template <typename... U>
    c_function_impl_t(fnt_ptr_t f, U &&...u) noexcept : pycfun_kw{{make_argument<T>(std::forward<U>(u))...}, &cpp_name<R>}, f{f} {}

    // call it : simply convert all arguments and call f
    PyObject *call(PyObject * /*self*/, PyObject *args, PyObject *kwargs) const override {
      auto l = [&]<size_t... Is>(std::index_sequence<Is...>) { return f(this->arg_cast<T>(Is, args, kwargs)...); };
      if constexpr (std::is_same_v<void, R>) {
        l(std::make_index_sequence<sizeof...(T)>{});
        Py_RETURN_NONE;
      } else
        return py_converter<R>::c2py(l(std::make_index_sequence<sizeof...(T)>{}));
    }
  };

  // ------------------  C method from a function ---------------------
  // implement pycfunction for a simple function
  template <typename R, typename Self, typename... T> class c_methfun_impl_t : public pycfun_kw {
    using fnt_ptr_t = R (*)(Self, T...);
    fnt_ptr_t f;

    public:
    // Note that U can be some pair of a DIFFERENT type than A::type, e.g. double x = 0 ...
    // As long as we can construc the A, it is fine
    template <typename U0, typename... U>
    c_methfun_impl_t(fnt_ptr_t f, U0, U &&...u) noexcept : pycfun_kw{{make_argument<T>(std::forward<U>(u))...}, &cpp_name<R>}, f{f} {}

    // call it : simply convert all arguments and call f
    PyObject *call(PyObject *self, PyObject *args, PyObject *kwargs) const override {
      auto l = [&]<size_t... Is>(std::index_sequence<Is...>) { return f(py2cxx<Self>(self), this->arg_cast<T>(Is, args, kwargs)...); };
      if constexpr (std::is_same_v<void, R>) {
        l(std::make_index_sequence<sizeof...(T)>{});
        Py_RETURN_NONE;
      } else
        return py_converter<R>::c2py(l(std::make_index_sequence<sizeof...(T)>{}));
    }
  };

  // -------------------C method --------------------
  // Same as before, but for a method of a class.
  // NB the const op is slighly different
  template <typename Cls, bool is_const, typename R, typename... T> class c_method_impl_t : public pycfun_kw {
    using fnt_ptr_t = std::conditional_t<is_const, R (Cls::*)(T...) const, R (Cls::*)(T...)>;
    fnt_ptr_t f;

    public:
    template <typename... U>
    c_method_impl_t(fnt_ptr_t f, U &&...u) noexcept : pycfun_kw{{make_argument<T>(std::forward<U>(u))...}, &cpp_name<R>}, f{f} {}

    PyObject *call(PyObject *self, PyObject *args, PyObject *kwargs) const override {
      auto l = [&]<size_t... Is>(std::index_sequence<Is...>) {
        // FIXME Why wrong ??
        //assert(py_converter<Cls>::is_convertible(self, false)); // true by construction
        // grab the class by reference, except std::function, cf callable
        decltype(auto) self_c = py_converter<Cls>::py2c(self);
        return (self_c.*f)(this->arg_cast<T>(Is, args, kwargs)...); // call the method
      };
      if constexpr (std::is_same_v<void, R>) {
        l(std::make_index_sequence<sizeof...(T)>{});
        Py_RETURN_NONE;
      } else
        return py_converter<R>::c2py(l(std::make_index_sequence<sizeof...(T)>{}));
    }
  };

  // -------------------C constructor from arguments--------------------
  // Same for a constructor
  // we have no function pointer, we just call Cls{}

  template <typename Cls, typename... T> class c_constructor_impl_t : public pycfun_kw {

    public:
    template <typename... U> c_constructor_impl_t(U &&...u) noexcept : pycfun_kw{{make_argument<T>(std::forward<U>(u))...}, {}} {}

    PyObject *call(PyObject *self, PyObject *args, PyObject *kwargs) const override {
      [&]<size_t... Is>(std::index_sequence<Is...>) {
        ((wrap<Cls> *)self)->_c = new Cls{this->arg_cast<T>(Is, args, kwargs)...}; //NOLINT
      }(std::make_index_sequence<sizeof...(T)>{});
      return (PyObject *)0x1; //NOLINT                                                        // rewritten in dispatcher_constructors_t as 0
    }
  };
  // -------------------C constructor from a maker --------------------
  // transform a maker of Cls into a constructor ...
  // Almost the same as before, except we put the maker between Cls and arguments
  template <typename Cls, typename... T> class c_maker_impl_t : public pycfun_kw {

    using maker_fnt_ptr_t = Cls (*)(T...);
    maker_fnt_ptr_t maker;

    public:
    template <typename... U>
    c_maker_impl_t(maker_fnt_ptr_t f, U &&...u) noexcept : pycfun_kw{{make_argument<T>(std::forward<U>(u))...}, {}}, maker{f} {}

    PyObject *call(PyObject *self, PyObject *args, PyObject *kwargs) const override {
      [&]<size_t... Is>(std::index_sequence<Is...>) {
        ((wrap<Cls> *)self)->_c = new Cls{maker(this->arg_cast<T>(Is, args, kwargs)...)}; //NOLINT
      }(std::make_index_sequence<sizeof...(T)>{});
      return (PyObject *)0x1; //NOLINT  rewritten in dispatcher_constructors_t as 0
    }
  };

  // ---------------  helper eraser functions to construct pycfunction ---------------
  // A are Arguments

  template <typename R, typename... T, typename... A> std::unique_ptr<pycfun_kw> cfun(R (*f)(T...), A &&...a) {
    static_assert(sizeof...(T) == sizeof...(A));
    return std::make_unique<c_function_impl_t<R, T...>>(f, std::forward<A>(a)...);
  }

  // FIXME : rename
  template <typename R, typename... T, typename... A> std::unique_ptr<pycfun_kw> cmethod(R (*f)(T...), A &&...a) {
    static_assert(sizeof...(T) == sizeof...(A));
    return std::make_unique<c_methfun_impl_t<R, T...>>(f, std::forward<A>(a)...);
  }

  template <typename Cls, typename R, typename... T, typename... A> std::unique_ptr<pycfun_kw> cfun(R (Cls::*f)(T...), A &&...a) noexcept {
    static_assert(sizeof...(T) == sizeof...(A));
    return std::make_unique<c_method_impl_t<Cls, false, R, T...>>(f, std::forward<A>(a)...);
  }

  template <typename Cls, typename R, typename... T, typename... A> std::unique_ptr<pycfun_kw> cfun(R (Cls::*f)(T...) const, A &&...a) {
    static_assert(sizeof...(T) == sizeof...(A));
    return std::make_unique<c_method_impl_t<Cls, true, R, T...>>(f, std::forward<A>(a)...);
  }

  // For inherited methods, we use cfun_B and pass the Cls explicitly in the generated code.
  // The issue comes from the fact that if A inherits for B, and we want to merge a method B:f into
  // A (e.g. B is not wrapped), the we may call the method &A::f BUT the compiler sees and matches
  // &B::f, so the dispatcher will not have the A class, but the B and will not be able to perform
  // the Python / C convertion of self properly.
  // We could use this version of cfun for all cases, but it is heavier, and in most ordinary cases Cls is matched correctly
  // and we do not have to write it explicitely, making the generated code lighter.

  template <typename Cls, typename ClsB, typename R, typename... T, typename... A>
  std::unique_ptr<pycfun_kw> cfun_B(R (ClsB::*f)(T...), A &&...a) noexcept {
    static_assert(std::is_base_of_v<ClsB, Cls>);
    static_assert(sizeof...(T) == sizeof...(A));
    return std::make_unique<c_method_impl_t<Cls, false, R, T...>>(f, std::forward<A>(a)...);
  }

  template <typename Cls, typename ClsB, typename R, typename... T, typename... A>
  std::unique_ptr<pycfun_kw> cfun_B(R (ClsB::*f)(T...) const, A &&...a) {
    static_assert(std::is_base_of_v<ClsB, Cls>);
    static_assert(sizeof...(T) == sizeof...(A));
    return std::make_unique<c_method_impl_t<Cls, true, R, T...>>(f, std::forward<A>(a)...);
  }

  template <typename Lambda, typename... A> auto cfun(Lambda l, A &&...a) {
    return cfun(+l, std::forward<A>(a)...); // + operator decays the lambda to a function pointer
  }

  template <typename Cls, typename... T, typename... A> std::unique_ptr<pycfun_kw> c_constructor(A &&...a) {
    static_assert(sizeof...(T) == sizeof...(A));
    return std::make_unique<c_constructor_impl_t<Cls, T...>>(std::forward<A>(a)...);
  }

  template <typename Cls, typename... T, typename... A> std::unique_ptr<pycfun_kw> c_maker(Cls (*f)(T...), A &&...a) {
    static_assert(sizeof...(T) == sizeof...(A));
    return std::make_unique<c_maker_impl_t<Cls, T...>>(f, std::forward<A>(a)...);
  }

  // ---------------------------------------------------------

  // pyfkw<d> transforms a static dispatcher_t<pycfun_kw, false>
  // into a C pointer PyCFunctionWithKeywords (Cf Python API)
  template <auto &dispatcher>
  static constexpr PyCFunctionWithKeywords pyfkw = [](PyObject *self, PyObject *args, PyObject *kwargs) { return dispatcher(self, args, kwargs); };

  // pyfkw_constructor<d> transforms a static dispatcher_t<pycfun_kw, true>
  // into a C pointer initproc (Cf Python API)
  template <auto &dispatcher>
  static constexpr initproc pyfkw_constructor = [](PyObject *self, PyObject *args, PyObject *kwargs) { return dispatcher(self, args, kwargs); };

} // namespace c2py
