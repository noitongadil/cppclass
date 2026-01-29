add_library(hw13 hw13.cpp)

target_include_directories(hw13 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${gtest_SOURCE_DIR}/include")
