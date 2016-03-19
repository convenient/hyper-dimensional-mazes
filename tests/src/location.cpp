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

TEST(location_test, euclidean_distance_basic) {

    Location a;
    a.addPoint("x", 1);

    Location b;
    b.addPoint("x", 6);

    double distance = a.getEuclideanDistanceTo(b);

    ASSERT_EQ(5, distance);
}

TEST(location_test, euclidean_distance_backwards) {

    Location a;
    a.addPoint("a", 5);

    Location b;
    b.addPoint("a", 0);

    double distance = a.getEuclideanDistanceTo(b);

    ASSERT_EQ(5, distance);
}


TEST(location_test, euclidean_distance_two_dimensional) {

    //These two points form a pretty typical 3/4/5 triangle.
    Location a;
    a.addPoint("a", 5);
    a.addPoint("b", 5);

    Location b;
    b.addPoint("a", 9); //4 difference
    b.addPoint("b", 8); //3 difference

    double distance = a.getEuclideanDistanceTo(b);

    ASSERT_EQ(5, distance);
}
