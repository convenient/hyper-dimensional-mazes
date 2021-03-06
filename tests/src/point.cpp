#include "gtest/gtest.h"
#include "graph/point.h"

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

TEST(point_test, get_neighbour_points) {
    Point test;
    test.addPosition("x", 0);
    test.addPosition("y", 0);

    std::vector<Point> neighbouringPoints = test.getNeighbouringPoints();

    Point a = neighbouringPoints.at(0);
    Point b = neighbouringPoints.at(1);
    Point c = neighbouringPoints.at(2);
    Point d = neighbouringPoints.at(3);

    ASSERT_EQ("(x:1)(y:0)", a.getAsString());
    ASSERT_EQ("(x:-1)(y:0)", b.getAsString());
    ASSERT_EQ("(x:0)(y:1)", c.getAsString());
    ASSERT_EQ("(x:0)(y:-1)", d.getAsString());
}

TEST(point_test, get_text_difference) {
    Point testA;
    testA.addPosition("x", 0);
    testA.addPosition("y", 0);

    Point testB;
    testB.addPosition("x", 1);
    testB.addPosition("y", 2);

    std::string differenceDescription = testA.getDifferenceDescription(testB);
    ASSERT_EQ("positive 1 on x, positive 2 on y", differenceDescription);
}

TEST(point_test, get_text_difference_negative) {
    Point testA;
    testA.addPosition("x", 0);
    testA.addPosition("y", 0);

    Point testB;
    testB.addPosition("x", -1);
    testB.addPosition("y", 2);

    std::string differenceDescription = testA.getDifferenceDescription(testB);
    ASSERT_EQ("negative 1 on x, positive 2 on y", differenceDescription);
}
