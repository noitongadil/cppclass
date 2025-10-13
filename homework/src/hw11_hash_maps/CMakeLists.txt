add_library(hw11 hw11.cpp)

target_include_directories(hw11 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${gtest_SOURCE_DIR}/include")
target_include_directories(hw11 PUBLIC ${xxhash_SOURCE_DIR})

target_link_libraries(hw11 PUBLIC xxhash)
