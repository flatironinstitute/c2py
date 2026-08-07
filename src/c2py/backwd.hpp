#pragma once
#include "./converters/wrapped.hpp"
#include "./py_range.hpp"

// Backward compatibility with the wrapping code generated for c2py 0.1, so that a project can be
// rebuilt against this c2py without regenerating its .wrap.cxx with the matching clair-c2py.
// TODO : remove this when C2PY_VERSION is bumped > 1.0.
//
// Nothing here is used by the code generated for this version, and nothing here should be used in
// new code : it only makes the older generated code compile.
//
// The 0.1 generated init function did :
//
//   if (PyType_Ready(&c2py::wrap_pytype<c2py::py_range>) < 0) return NULL;
//   ...
//   auto &conv_table = *c2py::conv_table_sptr.get();
//   conv_table[std::type_index(typeid(c2py::py_range)).name()] = &c2py::wrap_pytype<c2py::py_range>;
//   #define _add_type(T, N) c2py::add_type_object_to_main<T>(N, m, conv_table)
//
// i.e. it wrote the PyTypeObject table itself, through a table c2py handed out. The registration now
// goes through register_pto_in_table, which keeps the first registration and rejects a conflicting
// one, so the table is no longer handed out : what the old code writes into is a dummy, and the real
// registration is done by conv_table_sptr and add_type_object_to_main below.
//
// The version check does not stand in the way : it lives in version_check.hpp, which only the code
// generated for 1.0 includes. The 0.1 check was in c2py.hpp, where it never fired, since the user's
// code includes c2py.hpp long before the generated code defines C2PY_VERSION_MAJOR/MINOR.

// The 0.1 enum tables are generated as std::map<E, str_t>. str_t was a global alias to std::string
// leaked by serialization/as_tuple.hpp, which the plugin used and which has since been dropped.
using str_t = std::string;

namespace c2py {

  namespace backwd {

    // Stands in for the std::shared_ptr<pto_table_t> the 0.1 generated init used to get the table
    // from. It only ever reached it as *conv_table_sptr.get(), so a shared_ptr is not needed, and
    // get() is the one place from which we know that old generated code is initializing a module :
    // that is where the types c2py wraps itself get registered, which the 1.0 generated init does
    // explicitly and the 0.1 one did by writing py_range into the table below. Doing it in
    // add_type_object_to_main would not be enough : a module may wrap no type at all and still
    // convert to py_range, as test/generator does. Doing it when this object is initialized would
    // run it at dlopen, before the init function, and for every module rather than the old ones.
    //
    // A failure only leaves a Python exception set, since the old code checks nothing here. CPython
    // turns that into a SystemError when the init function returns non-NULL with an error set, so the
    // import still fails, only with a less direct message.
    struct conv_table_sptr_t {
      // The table the old code writes into : write-only, its entries reach nothing.
      [[nodiscard]] pto_table_t *get() const {
        static pto_table_t ignored_table; //NOLINT
        (void)register_internal_types();
        return &ignored_table;
      }
    };

  } // namespace backwd

  static constexpr backwd::conv_table_sptr_t conv_table_sptr = {}; //NOLINT

  // The 0.1 signature. The table argument is ignored, cf conv_table_sptr. The result is discarded by
  // the old code, with the consequence described above.
  // static, like the overload it forwards to, and maybe_unused since only 0.1 generated code calls it.
  template <typename T>
  [[maybe_unused]] static bool add_type_object_to_main(const char *pyname, PyObject *_main_, pto_table_t & /*ignored*/) noexcept {
    return add_type_object_to_main<T>(pyname, _main_);
  }

  // For the wrapping code generated between 0.1 and 1.0, which passed the table here.
  inline bool register_internal_types(pto_table_t & /*ignored*/) noexcept { return register_internal_types(); }

} // namespace c2py
