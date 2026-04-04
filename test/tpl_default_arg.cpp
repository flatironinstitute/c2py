#include <c2py/c2py.hpp>

// Template function with by-value parameter and braced-init default.
// When generating bindings for the explicit instantiation, the parameter type
// must be resolved (e.g. "int"), not the unresolved template parameter name.
template <typename T>
T by_value(T v = {}) { return v; }

// Template function with const-ref parameter and braced-init default.
// Requires both type resolution and cv-qualifier stripping to produce
// a valid constructible type (e.g. "int{}" not "const int &{}").
template <typename T>
T const_ref(const T &v = {}) { return v; }

template int by_value<int>(int);
template int const_ref<int>(int const &);

#include "tpl_default_arg.wrap.cxx"
