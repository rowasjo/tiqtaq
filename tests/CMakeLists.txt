
add_executable(row_tiqtaq_tests
  test.cpp)

target_link_libraries(row_tiqtaq_tests PRIVATE
  row_tiqtaqcore
  Catch2::Catch2WithMain)

catch_discover_tests(row_tiqtaq_tests)
