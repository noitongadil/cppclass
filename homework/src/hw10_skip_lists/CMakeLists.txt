add_library(hw10 hw10.cpp)

target_include_directories(hw10 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${gtest_SOURCE_DIR}/include")
