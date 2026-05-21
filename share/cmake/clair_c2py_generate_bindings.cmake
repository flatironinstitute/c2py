function(clair_c2py_generate_bindings module_name)
  # optional arguments:
  #   DIR: module directory relative to the current source dir (default: current source dir)
  #   TARGET: cmake target name (default: module_name)
  cmake_parse_arguments(ARG "" "DIR;TARGET" "" ${ARGN})

  if (NOT DEFINED ARG_TARGET)
    set(ARG_TARGET ${module_name})
  endif()

  set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}")
  set(bin_dir "${CMAKE_CURRENT_BINARY_DIR}")
  if (ARG_DIR)
    if (IS_ABSOLUTE "${ARG_DIR}")
      message(FATAL_ERROR "clair_c2py_generate_bindings: DIR must be relative to the current source dir (got '${ARG_DIR}')")
    endif()
    set(src_dir "${src_dir}/${ARG_DIR}")
    set(bin_dir "${bin_dir}/${ARG_DIR}")
  endif()

  set(cpp_src  "${src_dir}/${module_name}.cpp")
  set(wrap_cxx "${src_dir}/${module_name}.wrap.cxx")   # Python bindings file
  set(wrap_hxx "${src_dir}/${module_name}.wrap.hxx")   # Converter declarations (included by dependent modules)
  set(depfile  "${bin_dir}/${module_name}.cpp.d")      # dependency file

  file(MAKE_DIRECTORY "${bin_dir}")

  # In-tree clair build: use the build target directly and rebuild bindings when the tool is recompiled.
  # Otherwise (downstream projects): find the installed clair-c2py in PATH.
  if (TARGET clair-c2py)
    set(_clair_c2py_cmd clair-c2py)
    set(_clair_c2py_dep clair-c2py)
  else()
    find_program(CLAIR_C2PY_EXECUTABLE clair-c2py REQUIRED)
    set(_clair_c2py_cmd ${CLAIR_C2PY_EXECUTABLE})
  endif()

  add_custom_command(
    OUTPUT ${wrap_cxx} ${wrap_hxx} ${depfile}                                                              # Generates the .wrap.cxx, .wrap.hxx and dependency files
    COMMAND ${_clair_c2py_cmd} -p ${PROJECT_BINARY_DIR} --generate-depfile ${depfile} ${module_name}.cpp   # -p path/to/compile/commands
    DEPENDS ${cpp_src} ${_clair_c2py_dep}                                                                  # Rebuild when source or tool changes
    WORKING_DIRECTORY ${src_dir}                                                                           # Execute in source directory
    DEPFILE ${depfile}                                                                                     # Specify dependency file
  )

  add_custom_target(${ARG_TARGET}_bindings_generation DEPENDS ${wrap_cxx}) # We make the module depend on the bindings
  add_dependencies(${ARG_TARGET} ${ARG_TARGET}_bindings_generation)        # so that the generation happens before the compilation

endfunction()

