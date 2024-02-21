file(GLOB_RECURSE sources *.cpp)
add_library(c2py ${sources})
add_library(c2py::c2py ALIAS c2py)

# Enable warnings
target_link_libraries(c2py PRIVATE $<BUILD_INTERFACE:c2py_warnings>)

# Configure target and compilation
target_compile_features(c2py PUBLIC cxx_std_20)
set_target_properties(c2py PROPERTIES
  POSITION_INDEPENDENT_CODE ON
  VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
target_include_directories(c2py PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)
target_include_directories(c2py SYSTEM INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_FULL_INCLUDEDIR}>)

# Disable the inclusion of the deprecated Numpy API headers starting from 1.8.0.
if(Python_NumPy_VERSION VERSION_GREATER "1.8.0")
  target_compile_definitions(c2py PUBLIC NPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION)
endif()

# Install library and headers
install(TARGETS c2py EXPORT c2py-targets DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")


# ========= Additional Depdencies ==========

# Python and Numpy
target_link_libraries(c2py PUBLIC  Python::NumPy Python::Python)


# ========= Dynamic Analyzer Checks ==========

option(ASAN OFF "Compile library and executables with LLVM Address Sanitizer")
if(ASAN)
  if(NOT TARGET asan)
    find_package(sanitizer REQUIRED COMPONENTS asan)
  endif()
  target_link_libraries(c2py PUBLIC $<BUILD_INTERFACE:asan>)
endif()

option(UBSAN OFF "Compile library and executables with LLVM Undefined Behavior Sanitizer")
if(UBSAN)
  if(NOT TARGET ubsan)
    find_package(sanitizer REQUIRED COMPONENTS ubsan)
  endif()
  target_link_libraries(c2py PUBLIC $<BUILD_INTERFACE:ubsan>)
endif()

option(MSAN OFF "Compile library and executables with LLVM Memory Sanitizer")
if(MSAN)
  if(NOT TARGET msan)
    find_package(sanitizer REQUIRED COMPONENTS msan)
  endif()
  target_link_libraries(c2py PUBLIC $<BUILD_INTERFACE:msan>)
endif()

option(TSAN OFF "Compile library and executables with LLVM Thread Sanitizer")
if(TSAN)
  if(NOT TARGET tsan)
    find_package(sanitizer REQUIRED COMPONENTS tsan)
  endif()
  target_link_libraries(c2py PUBLIC $<BUILD_INTERFACE:tsan>)
endif()
