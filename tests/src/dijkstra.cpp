#include "gtest/gtest.h"
#include "dijkstra.h"

TEST(dijkstratest, base_path_find) {

    Point p1;
    p1.addPosition("a", 0);
    p1.addPosition("b", 0);

    Node n1 = Node(p1);
    Node *n1Ptr = &n1;

    Point p2;
    p2.addPosition("a", 1);
    p2.addPosition("b", 0);

    Node n2 = Node(p2);
    Node *n2Ptr = &n2;

    n1Ptr->link(n2Ptr);

    Dijkstra dijkstraPathSolver;

    std::vector<Node *> shortestPath = dijkstraPathSolver.getPath(n1Ptr, n2Ptr);

    ASSERT_EQ(2, shortestPath.size());

    std::vector<Node *> expectedPath;
    expectedPath.push_back(n1Ptr);
    expectedPath.push_back(n2Ptr);
    ASSERT_EQ(expectedPath, shortestPath);
}

TEST(dijkstratest, simple_path_find) {

}
