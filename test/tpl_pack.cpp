#include <c2py/c2py.hpp>

// Test code generation for template parameter packs.

// Deduced type (G) after a template parameter pack (Ns...).
// When Ns... is empty, G must be deduced, not explicitly specified.
template <int N = 0, int... Ns, typename G> auto deduced_after_pack(G g) { return g + N; }

template auto deduced_after_pack(int);
template auto deduced_after_pack(double);

// Function parameter pack (Args...).
// When Args... is empty, no extra parameter names should be emitted.
// When sizeof...(Args) > 1, parameter names should be unique.
template <typename G, typename... Args> auto fn_param_pack(G g, Args... args) {
  return g + static_cast<int>(sizeof...(args));
}

template auto fn_param_pack(int);
template auto fn_param_pack(int, double);
template auto fn_param_pack(int, double, char);

// =============== Declare module ===========================

#include "tpl_pack.wrap.cxx"
