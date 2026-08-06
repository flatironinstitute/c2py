#pragma once

#define PY_ARRAY_UNIQUE_SYMBOL _cpp2py_ARRAY_API

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
#include "converters/stl/tuple.hpp"
#include "converters/stl/set.hpp"
#include "converters/stl/array.hpp"
#include "converters/stl/string.hpp"
#include "converters/stl/variant.hpp"
#include "converters/stl/vector.hpp"
#include "converters/stl/function.hpp"
#include "converters/stl/span.hpp"
//#include "converters/misc.hpp"

// Last : it only patches up what the wrapping code generated for c2py 0.1 needs, and uses the above.
#include "backwd.hpp"
