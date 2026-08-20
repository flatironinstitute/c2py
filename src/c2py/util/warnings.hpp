#pragma once

// The library declares static function templates on purpose : several of them read the per-module
// statics pto_cache<T> and wrap_pytype<T>, which must not be merged across modules. The per-TU copies
// that -Wunused-template flags cost nothing here, since a module is one TU.
// The warning is reported at the declaration's location, so every header declaring such a template
// brackets its declarations with these macros : any of them may be included first, on its own.
#ifdef __clang__
#define C2PY_UNUSED_TEMPLATE_WARNING_OFF _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wunused-template\"")
#define C2PY_UNUSED_TEMPLATE_WARNING_ON _Pragma("clang diagnostic pop")
#else
#define C2PY_UNUSED_TEMPLATE_WARNING_OFF
#define C2PY_UNUSED_TEMPLATE_WARNING_ON
#endif

// Conversion from a string literal to char * : -Wwrite-strings for gcc, -Wwritable-strings for clang,
// which takes the gcc spelling as well, so one pragma covers both. Neither warns on the library as it
// stands : this is kept for icc, which did. c2py.hpp brackets its include block with it.
#ifdef __GNUC__ // clang defines it too
#define C2PY_WRITE_STRINGS_WARNING_OFF _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wwrite-strings\"")
#define C2PY_WRITE_STRINGS_WARNING_ON _Pragma("GCC diagnostic pop")
#else
#define C2PY_WRITE_STRINGS_WARNING_OFF
#define C2PY_WRITE_STRINGS_WARNING_ON
#endif
