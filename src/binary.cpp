#include "mazebinary.h"
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
    for (auto p : neighbouringPoints) {
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


int main(int argc, char **argv) {

    opengl graphics(argc, argv, render);

    MazeBinary maze;

    int mazeSize = 12;
    int minpart = (int)floor(mazeSize/2) * -1;
    int maxpart = (int)ceil(mazeSize/2);

    for (int x=minpart; x<maxpart; x++) {
        for (int y=minpart; y<maxpart; y++) {
            Point p;
            p.addPosition("x", x);
            p.addPosition("y", y);
            maze.createNode(p);
        }
    }

    maze.generate();

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
