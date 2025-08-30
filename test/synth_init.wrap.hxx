#include <c2py/c2py.hpp>

#ifndef C2PY_HXX_DECLARATION_synth_init_GUARDS
#define C2PY_HXX_DECLARATION_synth_init_GUARDS
template <> constexpr bool c2py::is_wrapped<N1::A_ndc>                   = true;
template <> inline constexpr auto c2py::tp_name<N1::A_ndc>               = "synth_init.ANdc";
template <> constexpr bool c2py::is_wrapped<N1::params>                  = true;
template <> inline constexpr auto c2py::tp_name<N1::params>              = "synth_init.Params";
template <> constexpr bool c2py::is_wrapped<N1::params_ndc>              = true;
template <> inline constexpr auto c2py::tp_name<N1::params_ndc>          = "synth_init.ParamsNdc";
template <> constexpr bool c2py::is_wrapped<N1::tpl_params_ndc<int>>     = true;
template <> inline constexpr auto c2py::tp_name<N1::tpl_params_ndc<int>> = "synth_init.TplParamNdcInt";
#endif