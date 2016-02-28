#include "gtest/gtest.h"
#include "binary.h"

TEST(basic_check, test_eq) {
    binary testObject;
    EXPECT_EQ(1337, testObject.leet());
}
