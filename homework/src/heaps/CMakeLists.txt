add_library(heap heap.cpp)

target_include_directories(heap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${gtest_SOURCE_DIR}/include")
