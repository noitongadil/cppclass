add_library(hw12 hw12.cpp)

target_include_directories(hw12 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${gtest_SOURCE_DIR}/include")
