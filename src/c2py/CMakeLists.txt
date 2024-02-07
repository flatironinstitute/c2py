add_library(c2py_obj OBJECT pyref.cpp pyfunction.cpp dyn_dispatch/pycfun_kw.cpp 
                       converters/wrapped.cpp converters/numpy_proxy.cpp)

target_compile_features(c2py_obj PRIVATE cxx_std_20)
set_property(TARGET c2py_obj PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(c2py_obj
  PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
  )

target_link_libraries(c2py_obj PRIVATE ${PROJECT_NAME}_warnings) 
target_link_libraries(c2py_obj PUBLIC Python::NumPy Python::Python)

add_library(c2py STATIC $<TARGET_OBJECTS:c2py_obj>)
add_library(c2py::c2py ALIAS c2py)

target_include_directories(c2py
  PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
  )

# Disable the inclusion of the deprecated Numpy API headers starting from 1.8.0. This seems to be buggy for earlier versions.
if(Python_NumPy_VERSION VERSION_GREATER "1.8.0")
  set_property(TARGET c2py PROPERTY INTERFACE_COMPILE_DEFINITIONS NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION)
  target_compile_definitions(c2py_obj PUBLIC NPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION)
endif()


target_link_libraries(c2py PUBLIC  Python::NumPy Python::Python)

# Install the library in lib and export the c2py target
install(TARGETS c2py EXPORT c2py-targets DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")

# Install the exported targets
install(EXPORT c2py-targets NAMESPACE c2py:: DESTINATION lib/cmake/c2py)
