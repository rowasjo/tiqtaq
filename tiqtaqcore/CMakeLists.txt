
qt_add_library(row_tiqtaqcore
  src/computer.cpp
  src/game.cpp
  src/gameviewcontroller.cpp
  include/row/tiqtaq/computer.hpp
  include/row/tiqtaq/game.hpp
  include/row/tiqtaq/gameviewcontroller.hpp)

target_link_libraries(row_tiqtaqcore PUBLIC Qt6::Widgets)

target_include_directories(row_tiqtaqcore PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>)

set_target_properties(
  row_tiqtaqcore PROPERTIES
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION ${PROJECT_VERSION}
  EXPORT_NAME tiqtaq
  AUTOMOC ON)

add_library(row_tiqtaqcore::tiqtaq ALIAS row_tiqtaqcore)

include(GenerateExportHeader)
generate_export_header(row_tiqtaqcore EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/row/row_tiqtaqcore_export.h)

install(TARGETS row_tiqtaqcore EXPORT row_tiqtaqTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
          COMPONENT row_tiqtaq_Runtime
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
          COMPONENT row_tiqtaq_Runtime
          NAMELINK_COMPONENT row_tiqtaq_Development
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
          COMPONENT row_tiqtaq_Development
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT row_tiqtaq_Development)

install(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT row_tiqtaq_Development)
