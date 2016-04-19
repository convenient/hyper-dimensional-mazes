#include "gtest/gtest.h"
#include "dijkstra.h"
#include "mazetestcase.h"

TEST(dijkstratest, base_path_find) {
    MazeTestCase maze;

    Point p1;
    p1.addPosition("a", 0);
    p1.addPosition("b", 0);

    Node *n1 = maze.createNode(p1);

    Point p2;
    p2.addPosition("a", 1);
    p2.addPosition("b", 0);

    Node *n2 = maze.createNode(p2);
    n1->link(n2);

    Maze *mazePtr = &maze;

    std::vector<Node *> shortestPath = Dijkstra::getPath(mazePtr, p1, p2);

    ASSERT_EQ(2, shortestPath.size());

    std::vector<Node *> expectedPath;
    expectedPath.push_back(n1);
    expectedPath.push_back(n2);
    ASSERT_EQ(expectedPath, shortestPath);
}
