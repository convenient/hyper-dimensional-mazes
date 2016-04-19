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

TEST(dijkstratest, simple_path_find) {
    MazeTestCase maze;

    Node *lastNode = nullptr;
    for (int x=0; x<3; x++) {
        for (int y=0; y<3; y++) {
            Point p;
            p.addPosition("x", x);
            p.addPosition("y", y);

            Node *newNode = maze.createNode(p);
            if (lastNode == nullptr) {
                lastNode = newNode;
            } else {
                lastNode->link(newNode);
            };
        }
    }

    Point a;
    a.addPosition("x", 0);
    a.addPosition("y", 0);

    Point b;
    b.addPosition("x", 2);
    b.addPosition("y", 2);

    Maze *mazePtr = &maze;

    std::vector<Node *> shortestPath = Dijkstra::getPath(mazePtr, a, b);

    ASSERT_EQ(2, shortestPath.size());
}
