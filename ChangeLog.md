(changelog)=

# Changelog

## Version 0.9.0

c2py 0.9.0 is a major release of the runtime library behind clair/c2py, the framework for
automatic C++ → Python bindings generation. It is the result of a long development effort
since the initial 0.1 series and tracks the clair 0.9.0 tool release. The headline changes
are:

* **Wider C++ coverage**: runtime support for wrapped-class properties (including inherited
  getters and setters), returning references to members at any depth with guardian-based
  lifetime management, a broad set of operators, enums (nested and cross-module), and
  function / class templates with parameter packs.
* **Automatic documentation**: overloaded functions expose NumPy-style docstrings built from
  the Python parameter and return types, with per-type documentation (`tp_doc` /
  `tp_ctor_doc`) set at runtime.
* **Richer type converters**: bounds-checked converters for 16-bit-and-wider integers,
  `std::vector<T>` for non-default-constructible `T`, reference converters that expect a
  guardian, and STL `tp_name`s.
* **CMake integration**: the `clair_c2py_generate_bindings` function and the `c2py_add_module`
  helper macro, both exposed to sub-project consumers, alongside a project-structure overhaul.
* **Toolchain**: builds with Clang 20 and Python 3.13, with continued GCC 13/14 support and an
  improved Python version check.
* Fixes several reference-counting, argument-lifetime and arithmetic issues.

We thank all contributors: Thomas Hahn, Olivier Parcollet, Nils Wentzell

Find below an itemized list of changes in this release.

### General
* Support properties on wrapped classes, including inherited getters and setters.
* Support returning references, including references to a member of a member at any depth,
  with a guardian managing the referent's lifetime.
* Wrap enums: set their `tp_name`, and support nested enums and cross-module enum use.
* Wrap function and class templates, including template parameter packs (#15) and template
  members with default arguments (#18).
* Support in-class friend function definitions (#17).
* Support class and method renaming (#7).
* Implement `tp_hash` for wrapped types.
* Extend the `py_converter` to 16-bit-and-wider integer types with bounds checking.
* Convert `std::vector<T>` for a non-default-constructible `T`, and set `tp_name`s for STL
  converters.
* Add the `C2PY_DEPRECATED_PARAMETER_NAME` annotation for backward-compatible parameter
  renaming.
* Improve the handling of default arguments (#12), including braced-init and specialization
  defaults.
* Preserve typedef names in the generated bindings.
* Include the h5 wrapping-information header and adjust the serialization API to match
  triqs/unstable.
* Port to Clang 20 and Python 3.13; keep GCC 13/14 support and work around clang-19's
  fold-expression limit.
* Improve the Python version check to compare only major and minor versions (#1).
* Use `unique_ptr` in the wrapped-type machinery to lower memory usage.
* Fix reference counting in various places.
* Fix a convertibility check for wrapped classes.
* Fix argument-lifetime issues for function arguments.
* Fix `operator[]` for template classes.
* Silence compiler warnings across GCC and Clang, including the NumPy deprecated-API warning.

### operators
* Wrap the function-call operator, subscript (`operator[]`), `operator<<`, unary minus, left
  shift, and in-place operators.

### doc
* Build NumPy-style docstrings for functions from their Python parameter and return types,
  handling multiple overloads (`dispatcher_t::doc`).
* Set `tp_doc` / `tp_ctor_doc` for wrapped types at runtime and add a brief first-line
  description to docstrings.

### cmake
* Add the `clair_c2py_generate_bindings` function and expose it to sub-project consumers.
* Add the `c2py_add_module` helper macro.
* Link modules against `Python::Module` rather than `Python::Python`.
* Force c2py to be a static library to avoid NumPy linking issues.
* Disable C++20 module scanning for the c2py target.
* Report the detected `clair-c2py` version.
* Use `GNUInstallDirs` more consistently and change the project language to CXX only.
* Overhaul the CMake files and project structure.

### jenkins
* Synchronize the Jenkinsfile with app4triqs and rename `Dockerfile.build` to `Dockerfile`.
* Use GCC 14 and Python 3.12 for macOS builds.

### ghactions
* Synchronize the GitHub Actions workflow with clair and update to Ubuntu 24.04.

### san
* Add a preload for compiling the tests with clair under sanitizers.
