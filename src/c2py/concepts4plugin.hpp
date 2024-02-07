#pragma once
#include "user_api.hpp"
#include "py_converter.hpp"

// ==========  A set of concepts used by the compiler plugin =========
// They are parsed along c2py, grabed by the plugin which can then use
// them on types ...

namespace c2py::concepts {

  //---------------- force_instantiation_add_methods-------------------
  // To force the compiler to instantiate add_methods (in case the user has made a partial spe., cf plugin)
  template <typename T>
  concept force_instantiation_add_methods = requires {
    { c2py_module::add_methods_to<T>{} };
  };

  //---------------- HasSerializeLikeBoost-------------------

  struct fake_archive {};
  void operator&(fake_archive, auto) {}

  template <typename T>
  concept HasSerializeLikeBoost = requires(T x, fake_archive ar) {
    { x.serialize(ar, 0) };
  };

} // namespace c2py::concepts
