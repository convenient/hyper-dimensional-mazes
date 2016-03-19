#include "gtest/gtest.h"
#include "point.h"

TEST(point_test, get_point_value) {

    Point a;
    a.addPosition("x", 7);

    ASSERT_EQ(0, a.getPositionOnAxis("y"));
    ASSERT_EQ(7, a.getPositionOnAxis("x"));
}

TEST(point_test, get_point_as_string) {

    Point a;
    a.addPosition("x", 1);

    ASSERT_EQ("(x:1)", a.getAsString());

    a.addPosition("y", 9);

    ASSERT_EQ("(x:1)(y:9)", a.getAsString());

    a.addPosition("z", 99);
    ASSERT_EQ("(x:1)(y:9)(z:99)", a.getAsString());
}

TEST(point_test, euclidean_distance_basic) {

    Point a;
    a.addPosition("x", 1);

    Point b;
    b.addPosition("x", 6);

    double distance = a.getEuclideanDistanceTo(b);

    ASSERT_EQ(5, distance);
}

TEST(point_test, euclidean_distance_backwards) {

    Point a;
    a.addPosition("a", 5);

    Point b;
    b.addPosition("a", 0);

    double distance = a.getEuclideanDistanceTo(b);

    ASSERT_EQ(5, distance);
}


TEST(point_test, euclidean_distance_two_dimensional) {

    //These two points form a pretty typical 3/4/5 triangle.
    Point a;
    a.addPosition("a", 5);
    a.addPosition("b", 5);

    Point b;
    b.addPosition("a", 9); //4 difference
    b.addPosition("b", 8); //3 difference

    double distance = a.getEuclideanDistanceTo(b);

    ASSERT_EQ(5, distance);
}
