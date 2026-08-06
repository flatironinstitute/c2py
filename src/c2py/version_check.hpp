// NB : no #pragma once, and no include guard.
// The user's code typically includes c2py.hpp at the top of the file, and the generated
// wrapping code at the end. c2py.hpp is therefore included twice, and #pragma once makes the
// second include a no-op : a check placed in c2py.hpp would never see the version macros.
// This header is not included by c2py.hpp. It is included by the generated wrapping code only,
// right after it has defined C2PY_VERSION_MAJOR/MINOR.

// The clang plugin defines C2PY_VERSION_MAJOR/MINOR in the generated wrapping code.
// This checks that the versions are the same, i.e. that the generated code is indeed
// compiled with exactly the c2py version for which it was generated.
#define C2PY_VERSION_MAJOR_CURRENT 1
#define C2PY_VERSION_MINOR_CURRENT 0

// #error is not fatal : the compiler goes on and buries the message under the errors and warnings
// of the rest of the file. A missing include is fatal, so it is used to stop the compilation.
#ifndef C2PY_VERSION_MAJOR
#error "C2PY_VERSION_MAJOR/MINOR are not defined : this wrapping code predates the c2py version check. Regenerate the wrapping code with clair-c2py."
#include "__stopping_compilation__"
#endif

#if (C2PY_VERSION_MAJOR != C2PY_VERSION_MAJOR_CURRENT) or (C2PY_VERSION_MINOR != C2PY_VERSION_MINOR_CURRENT)
// #error does not expand macros, so the two versions are reported by the #pragma message just
// before it, as a note or a warning. An unrecognized #pragma is ignored, so a compiler without it
// only prints less.
#define C2PY_STRINGIFY_(x) #x
#define C2PY_STRINGIFY(x) C2PY_STRINGIFY_(x)
#pragma message("this c2py is version " C2PY_STRINGIFY(C2PY_VERSION_MAJOR_CURRENT) "." C2PY_STRINGIFY(C2PY_VERSION_MINOR_CURRENT))
#pragma message("the wrapping code was generated for version " C2PY_STRINGIFY(C2PY_VERSION_MAJOR) "." C2PY_STRINGIFY(C2PY_VERSION_MINOR))
#error "The two versions must match exactly : regenerate the wrapping code with clair-c2py."
#include "__stopping_compilation__"
#endif
