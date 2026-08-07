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
  template <typename T> [[maybe_unused]] static pto_lookup_t lookup_pto() {
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
  // Two modules wrapping the same T each register their own wrap_pytype<T> : it has internal linkage,
  // and so does the add_type_object_to_main<T> that reads it, so no image shares either. The two
  // Python types are distinct, on every platform.
  //
  // The table is where we make this consistent : keep the first registration rather than let the last
  // import win, and refuse a second, *different* PyTypeObject for a type already registered (cf
  // add_type_object_to_main).
  PyTypeObject *register_pto_in_table(const char *mangled_name, PyTypeObject *pto);

  // ... and in the legacy cpp2py table, creating it if no legacy module has. This is what makes a T
  // wrapped here usable by a module built with the legacy cpp2py : its holder only ever reads _c,
  // which is at the same offset in wrap<T>.
  void register_pto_in_legacy_table(const char *mangled_name, PyTypeObject *pto);

  // Expose pto in the module namespace under pyname, and register it. Returns false, with a Python
  // exception set, if the module can not be initialized : the generated init then returns NULL, i.e.
  // the import fails with that exception. Nothing here depends on the wrapped C++ type, which enters
  // only through pto, its mangled name and its doc.
  [[nodiscard]] bool add_type_object_to_main_impl(const char *pyname, PyObject *_main_, PyTypeObject *pto, const char *mangled_name,
                                                  const char *doc) noexcept;

  // Same, for the type T wrapped by this module.
  //
  // static is important here, like the wrap_pytype<T> it reads : both are per module, so the type registered here is
  // this module's, inlined or not.
  // tp_doc<T> is a global const std::string with static storage duration; .data() is valid for the
  // lifetime of the shared library (Python finalization precedes dlclose).
  template <typename T> [[nodiscard, maybe_unused]] static bool add_type_object_to_main(const char *pyname, PyObject *_main_) noexcept {
    return add_type_object_to_main_impl(pyname, _main_, &c2py::wrap_pytype<T>, typeid(T).name(), c2py::tp_doc<T>.data());
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
