#include "maze.h"
#include "opengl.h"

#include <unistd.h>

using namespace std;

void drawNode(Node *node) {
    GLfloat squareSize = 0.1;

    Point nodePosition = node->getPoint();

    int nodePositionX = nodePosition.getPositionOnAxis("x");
    int nodePositionY = nodePosition.getPositionOnAxis("y");

    GLfloat xOffset = squareSize * nodePositionX;
    GLfloat yOffset = squareSize * nodePositionY;

    bool isLinkedUp = false;
    bool isLinkedDown = false;
    bool isLinkedLeft = false;
    bool isLinkedRight = false;

    //Foreach point adjacent to the current node
    std::vector<Point> neighbouringPoints = nodePosition.getNeighbouringPoints();
    for(std::vector<Point>::reverse_iterator it = neighbouringPoints.rbegin(); it != neighbouringPoints.rend(); ++it) {
        Point p = *it;
        if (node->isLinked(p)) {

            int tmpNodePositionX = p.getPositionOnAxis("x");
            int tmpNodePositionY = p.getPositionOnAxis("y");

            /**
             * Is directional dimensionality only linked to how mazes are drawn?
             * Or do I need to figure out this upness/downness within the node itself?
             */
            if (tmpNodePositionX == nodePositionX) {
                if (tmpNodePositionY > nodePositionY) {
                    isLinkedUp = true;
                } else {
                    isLinkedDown = true;
                }
            } else if (tmpNodePositionY == nodePositionY) {
                if (tmpNodePositionX > nodePositionX) {
                    isLinkedRight = true;
                } else {
                    isLinkedLeft = true;
                }
            } else {
                exit(-1);
            }
        }
    }

    //getAllPointsWithin1
    //foreach point
    //  if the point is linked
    //      Figure out the linked directions, if up down etc, mark the bool of sides to draw
    //Go through and draw all lines if the bool is set

    glBegin(GL_LINES);

    if (!isLinkedDown) {
        //Horizontal line bottom
        glVertex2f(squareSize + xOffset, yOffset);
        glVertex2f(xOffset, yOffset);
    }

    if (!isLinkedLeft) {
        //Vertical line left
        glVertex2f(xOffset, yOffset);
        glVertex2f(xOffset, squareSize + yOffset);
    }

    if (!isLinkedUp) {
    //Horizontal line top
        glVertex2f(squareSize + xOffset, squareSize + yOffset);
        glVertex2f(xOffset, squareSize + yOffset);
    }

    if (!isLinkedRight) {
        //Vertical line right
        glVertex2f(squareSize + xOffset, squareSize + yOffset);
        glVertex2f(squareSize + xOffset, yOffset);
    }

    glEnd();
    glFlush();
//
    unsigned int microseconds = 30000;
    usleep(microseconds);
}

void render() {

}

Point create2DPoint(int x, int y) {
    Point p;
    p.addPosition("x", x);
    p.addPosition("y", y);
    return p;
}

void connectNodes(Maze* maze, int x1, int y1, int x2, int y2) {
    Point a;
    a.addPosition("x", x1);
    a.addPosition("y", y1);
    Point b;
    b.addPosition("x", x2);
    b.addPosition("y", y2);

    maze->connectNodes(a, b);
}

int main(int argc, char **argv) {

    opengl graphics(argc, argv, render);

    Maze maze;

    for (int x=-9; x<9; x++) {
        for (int y=-9; y<9; y++) {
            maze.createNode(create2DPoint(x, y));
        }
    }


    Maze *mazePtr = &maze;

    connectNodes(mazePtr, 0, 0, 0, 1);
    connectNodes(mazePtr, 0, 1, 0, 2);
    connectNodes(mazePtr, 0, 2, 0, 3);
    connectNodes(mazePtr, 0, 3, 0, 4);

    connectNodes(mazePtr, 0, 4, 1, 4);
    connectNodes(mazePtr, 1, 4, 2, 4);
    connectNodes(mazePtr, 2, 4, 3, 4);
    connectNodes(mazePtr, 3, 4, 4, 4);

    connectNodes(mazePtr, 4, 4, 4, 3);
    connectNodes(mazePtr, 4, 3, 4, 2);
    connectNodes(mazePtr, 4, 2, 4, 1);
    connectNodes(mazePtr, 4, 1, 4, 0);

    connectNodes(mazePtr, 4, 0, 3, 0);
    connectNodes(mazePtr, 3, 0, 2, 0);
    connectNodes(mazePtr, 2, 0, 1, 0);
    connectNodes(mazePtr, 1, 0, 0, 0);

    //Grey background
    glClearColor(0.75, 0.75, 0.75, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    for (auto i : maze.getMap()) {
        Node *node = i.second;
        drawNode(node);
    }

    graphics.startLoop();
    return 0;
}
