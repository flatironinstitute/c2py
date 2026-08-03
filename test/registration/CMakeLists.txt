# Modules that all wrap the same C++ type L, in different ways, so that a test can choose the
# import order it wants to check. They are hand-written : what they exercise is the registration
# itself, which the generated init only calls into. Clair can not generate these : see the note in
# L.hpp for why (in short, is_wrapped<L> = true tells it a wrapper already exists elsewhere, which is
# precisely what lets these modules each register their own, conflicting one by hand).
macro(c2py_add_registration_module m)
  Python_add_library(${m} MODULE ${m}.cpp)
  # As c2py_add_module does for the real modules. It matters here more than anywhere else: these
  # modules all wrap the same L, so they define the same strong tp_name<L> / typeinfo for L, and
  # only hidden visibility keeps those apart.
  set_target_properties(${m} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON)
  target_link_libraries(${m} PRIVATE c2py c2py_warnings)
  # clair adds c2py with EXCLUDE_FROM_ALL and pulls the test targets back into its own ALL target
  # through this list (cf clair/test/CMakeLists.txt). A module missing from it is simply not built
  # there, and the tests below then fail to import it.
  set(c2py_all_low_level_tests ${c2py_all_low_level_tests} ${m} CACHE INTERNAL "")
endmacro()

# One interpreter per scenario : the tables live in __main__ for the whole process and are never
# emptied, so the import order a test sets up can not be undone.
macro(c2py_add_registration_test name)
  add_test(NAME ${name}_py COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${name}_test.py WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  set_property(TEST ${name}_py APPEND PROPERTY ENVIRONMENT PYTHONPATH=${CMAKE_CURRENT_BINARY_DIR}:$ENV{PYTHONPATH} ${SANITIZER_RT_PRELOAD})
endmacro()

c2py_add_registration_module(use_L)
c2py_add_registration_module(c2py_a)
c2py_add_registration_module(c2py_b)

c2py_add_registration_test(not_registered)
c2py_add_registration_test(not_registered_overload)
c2py_add_registration_test(conflict)

# ------ Interoperability with the legacy cpp2py. All of this goes when cpp2py does. ------
c2py_add_registration_module(legacy_reg)
c2py_add_registration_test(legacy_only)
c2py_add_registration_test(legacy_then_c2py)
c2py_add_registration_test(legacy_after_c2py)
