#pragma once

// The clang plugin will define C2PY_VERSION_MAJOR/MINOR in the generated wrapping code,
// which includes c2py.
// This checks that the versions are the same, i.e. that the generated code is indeed
// compiled with exactly the c2py version for which it was generated.
#define C2PY_VERSION_MAJOR_CURRENT 0
#define C2PY_VERSION_MINOR_CURRENT 1
#ifdef C2PY_VERSION_MAJOR
#if (C2PY_VERSION_MAJOR != C2PY_VERSION_MAJOR_CURRENT) or (C2PY_VERSION_MINOR != C2PY_VERSION_MINOR_CURRENT)
#error "The wrapping code has been generated for a different version of c2py compared to the one included."
#endif
#endif

// The macro C2PY_INCLUDED is defined either here, when including the c2py
// or as a compiler option in the clair clang_plugin target to make
// sure it is always defined before the user's code, in case the user has not included c2py FIRST.
// Libraries will then be able to automatically include their converters/hxx
#ifndef C2PY_INCLUDED
#define C2PY_INCLUDED
#endif

// silence warning on intel
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-writable-strings"
#endif
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

// -- The various parts of the lib ---
// -- To reread the code, read in order --

#include "user_api.hpp"
#include "concepts4plugin.hpp"
#include "pyref.hpp"
#include "py_converter.hpp"
#include "pytypes/wrap.hpp"
#include "converters/wrapped.hpp"
#include "dyn_dispatch/dispatcher.hpp"
#include "py_range.hpp"
#include "pydict.hpp"
#include "pyfunction.hpp"
#include "pyinterpreter.hpp"

#include "serialization/as_tuple.hpp"
#include "serialization/repr.hpp"
// serialization/h5.hpp is not included by default. The plugin will include it case by case.

#include "converters/basic_types.hpp"
#include "converters/enums.hpp"
#include "converters/pydict.hpp"
#include "converters/stl/complex.hpp"
#include "converters/stl/map.hpp"
#include "converters/stl/optional.hpp"
#include "converters/stl/pair.hpp"
#include "converters/stl/set.hpp"
#include "converters/stl/array.hpp"
#include "converters/stl/string.hpp"
#include "converters/stl/variant.hpp"
#include "converters/stl/vector.hpp"
#include "converters/stl/function.hpp"
#include "converters/stl/span.hpp"
//#include "converters/misc.hpp"
