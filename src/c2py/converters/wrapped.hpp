#pragma once
#include "../py_converter.hpp"
#include "../pytypes/wrap.hpp"
#include <type_traits>

// Two global tables of PyTypeObject, stored at the top of the interpreter so that each module can
// retrieve the PyTypeObject of the types wrapped by the other modules :
//
//   __main__.__c2py_table    the types wrapped by the c2py modules. Written by c2py only.
//   __main__.__cpp2py_table  the table of the legacy cpp2py. Written by the legacy modules, and by
//                            c2py as well (cf register_pto_in_legacy_table).
//
// A lookup goes through the c2py table first. A type found only in the cpp2py table is wrapped by a
// module built with the legacy cpp2py, whose holder is { PyObject_HEAD; T *_c; } : it has no parent
// and no is_const field, so the converters can not treat it as a wrap<T>.
namespace c2py {

  // Table : c++ type name -> PyTypeObject *.
  // Public only because it is used in used in test/registration/legacy_reg.cpp since is the also layout of the legacy cpp2py table
  using pto_table_t = std::map<std::string, PyTypeObject *>;

  // The result of the lookup of a C++ type in the tables.
  struct pto_lookup_t {
    PyTypeObject *pto = nullptr; // null if the type is wrapped nowhere. A Python exception is then set.
    bool legacy       = false;   // pto comes from the legacy cpp2py table : holder without parent and is_const
  };

  // Look up ind in the c2py table, then in the legacy cpp2py table. Not meant to be called
  // directly : go through lookup_pto<T> below, which memoizes the result.
  pto_lookup_t lookup_pto_in_tables(std::type_index const &ind);

  // Memoized lookup of T caching lookup_pto_in_tables.
  // static, like wrap_pytype : one cache per module.
  template <typename T> static pto_lookup_t pto_cache = {}; //NOLINT

  // Only a hit in the c2py table is memoized. It never changes afterwards, since a registration
  // there keeps the entry already present (cf register_pto_in_table). The two other outcomes can :
  // a miss because a module registering T may be imported later, and a legacy hit because a c2py
  // module wrapping T may be imported later, and must then win as the c2py table is searched first.
  //
  // static, to match pto_cache. The chain stops here : the py_converter<T> members that call this are
  // class template members, which can not be given internal linkage.
  template <typename T> static pto_lookup_t lookup_pto() {
    auto r = pto_cache<T>;
    if (r.pto == nullptr) [[unlikely]] {
      r = lookup_pto_in_tables(typeid(T));
      if (not r.legacy) pto_cache<T> = r;
    }
    return r;
  }

  // Register pto in the c2py table, under the mangled name of the C++ type it wraps, keeping whatever
  // entry is already there. Returns the entry now in the table, i.e. pto unless another module got
  // there first.
  //
  // Whether two modules wrapping the same T end up sharing one wrap_pytype<T> is up to the loader.
  // wrap_pytype<T> has internal linkage, one copy per module, but the template instantiations that
  // use it are weak symbols : dyld coalesces those across images, so on macOS the second module runs
  // the first module's add_type_object_to_main<T>, hence its wrap_pytype<T>, while on Linux
  // RTLD_LOCAL keeps each module on its own copy and the two Python types stay distinct.
  //
  // The table is where we make this consistent : keep the first registration rather than let the last
  // import win, and refuse a second, *different* PyTypeObject for a type already registered (cf
  // add_type_object_to_main).
  PyTypeObject *register_pto_in_table(const char *mangled_name, PyTypeObject *pto);

  // ... and in the legacy cpp2py table, creating it if no legacy module has. This is what makes a T
  // wrapped here usable by a module built with the legacy cpp2py : its holder only ever reads _c,
  // which is at the same offset in wrap<T>.
  void register_pto_in_legacy_table(const char *mangled_name, PyTypeObject *pto);

  // Expose the PyTypeObject of T in the module namespace under pyname, and register it.
  // Returns false, with a Python exception set, if the module can not be initialized : the generated
  // init then returns NULL, i.e. the import fails with that exception.
  //
  // noexcept : this is called from PyInit, which is extern "C" and which CPython calls from C, so an
  // exception crossing that frame terminates the process instead of failing the import. The table
  // plumbing does throw (cf get_table_from_main), hence the function-try-block. Its handlers must not
  // throw either, which is why they report through PyErr_Format rather than build a std::string.
  template <typename T> [[nodiscard]] bool add_type_object_to_main(const char *pyname, PyObject *_main_) noexcept try {
    // tp_doc<T> is a global const std::string with static storage duration; .data() is valid
    // for the lifetime of the shared library (Python finalization precedes dlclose).
    c2py::wrap_pytype<T>.tp_doc = c2py::tp_doc<T>.data();
    Py_INCREF(&c2py::wrap_pytype<T>);
    // PyModule_AddObject steals the reference on success; release the INCREF on failure.
    if (PyModule_AddObject(_main_, pyname, (PyObject *)&c2py::wrap_pytype<T>) < 0) {
      Py_DECREF(&c2py::wrap_pytype<T>);
      return false;
    }
    auto const *mangled_name = std::type_index(typeid(T)).name();
    // Re-importing a module re-runs its init with the same wrap_pytype<T>, which is fine. A
    // *different* PyTypeObject means two c2py modules wrap this C++ type : objects of one would not
    // convert in the other, so refuse rather than let it be discovered later.
    auto *registered = register_pto_in_table(mangled_name, &c2py::wrap_pytype<T>);
    if (registered != &c2py::wrap_pytype<T>) {
      auto err = std::string{"c2py: the C++ type wrapped here as '"} + pyname + "' is already registered as '" + registered->tp_name
         + "' by another module. The two Python types are distinct and objects of one will not convert in the other. "
           "Wrap this C++ type in a single module and import it from there.";
      PyErr_SetString(PyExc_RuntimeError, err.c_str());
      return false;
    }
    register_pto_in_legacy_table(mangled_name, &c2py::wrap_pytype<T>);
    return true;
  } catch (std::exception const &e) {
    PyErr_Format(PyExc_ImportError, "c2py: can not register '%s' : %s", pyname, e.what()); // NOLINT
    return false;
  } catch (...) {
    PyErr_Format(PyExc_ImportError, "c2py: can not register '%s' : unknown C++ exception", pyname); // NOLINT
    return false;
  }

  //---------------------  wrapped type -----------------------------

  template <typename T>
    requires(is_wrapped<T> and not std::is_enum_v<T>)
  struct py_converter<T> {

    static_assert(not std::is_reference_v<T>); // The T = U& case is a separate specialization

    // A legacy cpp2py type needs no special case here : it holds a T it owns through _c, at the same
    // offset as in wrap<T>, and its dealloc deletes it. parent and is_const stay untouched.
    template <typename U> static PyObject *c2py(U &&x) {
      PyTypeObject *p = lookup_pto<T>().pto;
      if (p == nullptr) return nullptr;
      auto *self = (wrap<T> *)p->tp_alloc(p, 0);
      if (self != NULL) { self->_c = new T{std::forward<U>(x)}; } // NOLINT
      return (PyObject *)self;
    }

    static T &py2c(PyObject *ob) {
      auto *_c = ((wrap<T> *)ob)->_c;
      if (_c == NULL) {
        std::cerr << "Severe internal error : _c is null in py2c\n";
        std::terminate();
      }
      return *_c;
    }

    // specific to this converter. ob has passed is_convertible, i.e. it is an instance of the
    // PyTypeObject registered for T, so the lookup below describes its holder.
    static bool is_const(PyObject *ob) {
      if (lookup_pto<T>().legacy) return false; // a legacy holder has no is_const field, and owns a mutable T
      return ((wrap<T> *)ob)->is_const;
    }

    static bool is_convertible(PyObject *ob, bool raise_exception) {
      PyTypeObject *p = lookup_pto<T>().pto;
      if (p == nullptr) {
        // T is wrapped nowhere, and the lookup has set a RuntimeError. Clear it unless we were asked
        // to raise : this is a predicate, and the dispatcher calls it with raise_exception false to
        // try each overload in turn. A leftover error makes the *next* overload decline as well,
        // since a converter reads PyErr_Occurred to detect its own failure.
        if (not raise_exception) PyErr_Clear();
        return false;
      }
      if (PyObject_TypeCheck(ob, p)) {
        if (((wrap<T> *)ob)->_c != NULL) return true;
        auto err = std::string{"Severe internal error : Python object of "} + p->tp_name + " has a _c NULL pointer !!";
        if (raise_exception) PyErr_SetString(PyExc_TypeError, err.c_str());
        return false;
      }
      auto err = std::string{"Python object is not a "} + p->tp_name + " but a " + Py_TYPE(ob)->tp_name;
      if (raise_exception) PyErr_SetString(PyExc_TypeError, err.c_str());
      return false;
    }
  };

  // ------------------------------------

  template <typename T>
    requires(is_wrapped<std::remove_const_t<T>>)
  struct py_converter<T &> {
    // this converter is only used C-> Py. For Py-> C, the pycfun_kw takes care of the reference.
    // FIXME : it should not. The previous converter should return T, and we should use this one in pycfun_kw.
    static bool is_convertible(PyObject *ob, bool raise_exception) = delete;
    static T &py2c(PyObject *ob)                                   = delete;

    //
    static PyObject *c2py(T &x, PyObject *guardian) {
      auto [p, legacy] = lookup_pto<T>();
      if (p == nullptr) return nullptr;
      // A legacy cpp2py holder has no parent : it would delete the T we only borrow here, and its
      // tp_alloc would not even reserve the space for the parent and is_const we must write.
      if (legacy) [[unlikely]] {
        auto err = std::string{"Can not wrap a reference to "} + p->tp_name
           + " : its Python type is registered by a module built with the legacy cpp2py. Rebuild that module with c2py.";
        PyErr_SetString(PyExc_TypeError, err.c_str());
        return nullptr;
      }
      auto *self = (wrap<T> *)p->tp_alloc(p, 0);
      if (self != NULL) {
        self->_c       = &x;
        self->parent   = guardian;
        self->is_const = std::is_const_v<T>;
        Py_XINCREF(guardian); // parent owns a reference
      }
      return (PyObject *)self;
    }
    // p2yc and is_convertible are never used.
  };

} // namespace c2py
