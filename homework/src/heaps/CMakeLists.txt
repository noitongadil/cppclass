add_library(heap INTERFACE)

target_include_directories(heap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${gtest_SOURCE_DIR}/include")
