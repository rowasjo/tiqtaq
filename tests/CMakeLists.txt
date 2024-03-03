
add_executable(row_tiqtaq_tests
  gametests.cpp
  computertests.cpp)

target_link_libraries(row_tiqtaq_tests PRIVATE
  row_tiqtaqcore
  doctest)

include(doctest)
doctest_discover_tests(row_tiqtaq_tests)
