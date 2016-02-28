#Gtest
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#Project files
include_directories(${BASE_PROJECT_SOURCE_DIR})

add_executable(runTests
        binary.cpp
        googletest.cpp)

target_link_libraries(runTests gtest gtest_main)
