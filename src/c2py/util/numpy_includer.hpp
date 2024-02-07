#pragma once

// We need numpy to check/convert the scalar type of numpy into C++
#ifndef NPY_NO_DEPRECATED_API
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#endif

#include <numpy/ndarraytypes.h>
#include <numpy/arrayobject.h>
