configure_file(c2py-config.cmake.in c2py-config.cmake @ONLY)
configure_file(c2py-config-version.cmake.in c2py-config-version.cmake @ONLY)
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/c2py-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/c2py-config-version.cmake
  DESTINATION lib/cmake/c2py
)

install(EXPORT c2py-targets NAMESPACE c2py:: DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/c2py)
