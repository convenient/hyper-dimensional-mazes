#include "gtest/gtest.h"
#include "dijkstra.h"
#include "mazetestcase.h"

TEST(dijkstratest, base_path_find) {
    MazeTestCase maze;

    Point p1;
    p1.addPosition("a", 0);
    p1.addPosition("b", 0);

    maze.createNode(p1);

    Point p2;
    p2.addPosition("a", 1);
    p2.addPosition("b", 0);

    maze.createNode(p2);
    maze.connectNodes(p1, p2);

    Maze *mazePtr = &maze;

    Dijkstra::getPath(mazePtr, p1, p2);

}
