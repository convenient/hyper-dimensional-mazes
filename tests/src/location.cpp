#include "gtest/gtest.h"
#include "location.h"

TEST(location_test, get_location_as_string) {

    Location a;
    a.addPoint("x", 1);

    ASSERT_EQ("(x:1)", a.getAsString());

    a.addPoint("y", 9);

    ASSERT_EQ("(x:1)(y:9)", a.getAsString());

    a.addPoint("z", 99);
    ASSERT_EQ("(x:1)(y:9)(z:99)", a.getAsString());
}
