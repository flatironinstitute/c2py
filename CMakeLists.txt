cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
cmake_policy(VERSION ${CMAKE_VERSION})

# ############
# Define Project
project(c2py VERSION 0.1.0 LANGUAGES CXX)
get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

message(STATUS "-------- c2py version and git hash detection -------------")
find_package(Git)
execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  OUTPUT_VARIABLE PROJECT_GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "c2py version : ${PROJECT_VERSION}")
message(STATUS "c2py Git hash: ${PROJECT_GIT_HASH}")

# Assert that install directory is provided and is absolute path.
if(NOT IS_SUBPROJECT)
  if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OR (NOT IS_ABSOLUTE ${CMAKE_INSTALL_PREFIX}))
    message(FATAL_ERROR "No install prefix given (or invalid)")
  endif()
  message(STATUS "-------- CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX} --------")
endif()
set(c2py_BINARY_DIR ${PROJECT_BINARY_DIR} CACHE STRING "Binary directory of the c2py Project")

# Make additional Find Modules available
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/share/cmake/Modules)

# ############
# CMake Options

# Default to Release build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Type of build" FORCE)
endif()
if(NOT IS_SUBPROJECT)
  message(STATUS "-------- BUILD-TYPE: ${CMAKE_BUILD_TYPE} --------")
endif()

# Testing
option(Build_Tests "Build tests" ON)

# Regenerate the C++ Python bindings via clair-c2py for projects that use c2py_add_module.
# Default OFF: most builds consume the checked-in .wrap.cxx files. Set ON when iterating on
# bindings with clair installed.
option(Update_Python_Bindings "Regenerate the C++ Python bindings via clair-c2py" OFF)

# ############
# Global Compilation Settings

# Build a Debian package
option(BUILD_DEBIAN_PACKAGE "Build a deb package" OFF)

# Export the list of compile-commands into compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Disable compiler extensions
set(CMAKE_CXX_EXTENSIONS OFF)

# No C++20 modules used. Disable module scanning (default ON for C++20+ with Ninja):
# it injects transient @<obj>.modmap flags into compile_commands.json that break clair-c2py
# binding generation when it replays those commands. No-op on CMake < 3.28.
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# Provide additional debugging information for Debug builds
add_compile_options($<$<CONFIG:Debug>:-ggdb3>)

# Create an Interface target for compiler warnings
add_library(c2py_warnings INTERFACE)
target_compile_options(c2py_warnings
  INTERFACE
    -Wall
    -Wextra
    -Wfloat-conversion
    -Wpedantic
    -Wno-sign-compare
    $<$<CXX_COMPILER_ID:GNU>:-Wno-comma-subscript>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-psabi> # Disable notes about ABI changes
    $<$<CXX_COMPILER_ID:GNU>:-Wshadow=local>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-attributes>
    $<$<CXX_COMPILER_ID:GNU>:-Wno-deprecated-declarations>
    $<$<CXX_COMPILER_ID:AppleClang,Clang,IntelLLVM>:-Wno-deprecated-comma-subscript>
    $<$<CXX_COMPILER_ID:AppleClang,Clang,IntelLLVM>:-Wno-unknown-warning-option>
    $<$<CXX_COMPILER_ID:AppleClang,Clang,IntelLLVM>:-Wshadow>
    $<$<CXX_COMPILER_ID:AppleClang,Clang,IntelLLVM>:-Wno-gcc-compat>
    $<$<CXX_COMPILER_ID:AppleClang,Clang,IntelLLVM>:-Wno-c++26-extensions>
    $<$<CXX_COMPILER_ID:AppleClang,Clang,IntelLLVM>:-Wno-c++26-compat>
    $<$<CXX_COMPILER_ID:IntelLLVM>:-Wno-tautological-constant-compare>
)

# ---------------------------------
# Resolve Clang Linktime Problems
# CMake will adjust any linker flags from '-L path_to/mylib.so' to -lmylib
# if the proper mylib.so is automatically found by the linker, i.e.
# the directory comes first in LIBRARY_PATH.
# The clang linker however ignores LIBRARY_PATH.
# We thus explicitly add the content of LIBRARY_PATH to the LDFLAGS
# FIXME For future cmake versions we should populate the
# INTERFACE_LINK_DIRECTORIES of the target
# ---------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND DEFINED ENV{LIBRARY_PATH})
  string(REPLACE ":" ";" LINK_DIRS $ENV{LIBRARY_PATH})
  foreach(dir ${LINK_DIRS})
    string(APPEND CMAKE_SHARED_LINKER_FLAGS " -L${dir}")
    string(APPEND CMAKE_MODULE_LINKER_FLAGS " -L${dir}")
    string(APPEND CMAKE_EXE_LINKER_FLAGS " -L${dir}")
  endforeach()
endif()

# Provide GNU Installation directories
include(GNUInstallDirs)

# Python
message(STATUS "-------- Python detection -------------")
find_package(Python REQUIRED COMPONENTS Interpreter Development NumPy)
set(c2py_all_python_flags " -I${Python_INCLUDE_DIRS} -I${Python_NumPy_INCLUDE_DIRS} -L${Python_LIBRARY_DIRS} -lpython${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}")
set(c2py_all_python_include_flags " -I${Python_INCLUDE_DIRS} -I${Python_NumPy_INCLUDE_DIRS} ")
configure_file(c2py_flags.py.in c2py_flags @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/c2py_flags DESTINATION bin PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

# Expose reusable Python variables for downstream projects (triqs, h5, nda) that pull
# c2py in as a subproject, so they no longer each run find_package(Python) and recompute
# the install layout. These are CACHE variables so they cross the subproject scope.
# We keep the historical, un-prefixed names (Python_EXECUTABLE, PYTHON_LIB_DEST_ROOT,
# PYTHON_MODULE_EXT) so existing consumers and installed *-config files remain compatible.
set(Python_EXECUTABLE "${Python_EXECUTABLE}" CACHE FILEPATH "Python interpreter for the c2py/TRIQS stack")
if(Python_SOABI)
  set(PYTHON_MODULE_EXT .${Python_SOABI}.so CACHE STRING "Python module extension")
else()
  set(PYTHON_MODULE_EXT .so CACHE STRING "Python module extension")
endif()
if(BUILD_DEBIAN_PACKAGE)
  set(PYTHON_LIB_DEST_ROOT lib/python${Python_VERSION_MAJOR}/dist-packages CACHE PATH "Python module install destination (relative to the install prefix)")
else()
  set(PYTHON_LIB_DEST_ROOT lib/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages CACHE PATH "Python module install destination (relative to the install prefix)")
endif()

# #############
# Build Project

# Build and install the library
add_subdirectory(src/c2py)

# Tests
if(Build_Tests AND (NOT IS_SUBPROJECT OR IS_CLAIR_BUILD))
  set(H5_INCLUDE_DIR ${PROJECT_BINARY_DIR}/deps/h5_src/c++/)
  enable_testing()
  add_subdirectory(test)
endif()

# Additional configuration files
add_subdirectory(share)

# Make the c2py_add_module macro (and clair_c2py_generate_bindings) available
# to consumers that pull c2py in as a subproject (e.g. via CPMAddPackage). For
# the installed-package path it is included by c2py-config.cmake instead.
include(${PROJECT_SOURCE_DIR}/share/cmake/c2py_add_module.cmake)

# #############
# Debian Package

if(BUILD_DEBIAN_PACKAGE AND NOT IS_SUBPROJECT)
  if(NOT CMAKE_INSTALL_PREFIX STREQUAL "/usr")
    message(FATAL_ERROR "CMAKE_INSTALL_PREFIX must be /usr for packaging")
  endif()
  set(CPACK_PACKAGE_NAME c2py)
  set(CPACK_GENERATOR "DEB")
  set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
  set(CPACK_PACKAGE_CONTACT "https://github.com/flatironinstitute/c2py")
  execute_process(COMMAND dpkg --print-architecture OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE OUTPUT_STRIP_TRAILING_WHITESPACE)
  set(CPACK_DEBIAN_PACKAGE_DEPENDS "python")
  set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
  set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
  include(CPack)
endif()
