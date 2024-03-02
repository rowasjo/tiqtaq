
qt_add_executable(row_tiqtaq
    main.cpp)

target_link_libraries(row_tiqtaq PRIVATE row_tiqtaqcore::tiqtaq)

install(TARGETS row_tiqtaq
  EXPORT row_tiqtaqTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT row_tiqtaq_Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT row_tiqtaq_Runtime
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT row_tiqtaq_Development)

install(EXPORT row_tiqtaqTargets
  FILE row_tiqtaqTargets.cmake
  NAMESPACE row_tiqtaq::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/row_tiqtaq)
