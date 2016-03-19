#Gtest
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(${GOOGLE_TEST_SOURCE_DIR}/include ${GOOGLE_TEST_SOURCE_DIR})

#Project files
include_directories(${BASE_PROJECT_SOURCE_DIR})

add_executable(runTests
        agoogletest.cpp
        location.cpp
        )

target_link_libraries(runTests gtest gtest_main)
