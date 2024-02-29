
set(ROW_TiqTaq_INSTALL_CMAKEDIR
  ${CMAKE_INSTALL_LIBDIR}/cmake/row_tiqtaq
  CACHE STRING "")

cmake_print_variables(CMAKE_INSTALL_LIBDIR ROW_TiqTaq_INSTALL_CMAKEDIR)

install(EXPORT row_tiqtaqTargets
  FILE row_tiqtaqTargets.cmake
  NAMESPACE row_tiqtaq::
  DESTINATION ${ROW_TiqTaq_INSTALL_CMAKEDIR}
  COMPONENT row_tiqtaq_Development)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  row_tiqtaqConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/row_tiqtaqConfig.cmake
  INSTALL_DESTINATION ${ROW_TiqTaq_INSTALL_CMAKEDIR})

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/row_tiqtaqConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/row_tiqtaqConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/row_tiqtaqConfigVersion.cmake
  DESTINATION ${ROW_TiqTaq_INSTALL_CMAKEDIR}
  COMPONENT row_tiqtaq_Development)
