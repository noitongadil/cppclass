add_library(hw09 hw09.cpp)

target_include_directories(hw09 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${gtest_SOURCE_DIR}/include")
