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

Point create2DPoint(int x, int y) {
    Point p;
    p.addPosition("x", x);
    p.addPosition("y", y);
    return p;
}

void binaryAlgorithm(Maze *maze) {

    Node*workingNode = nullptr;
    if (workingNode == nullptr) {
        workingNode = maze->getRandomNode();
    }

    Point workingPoint = workingNode->getPoint();

    std::vector<Point> potentialPoints;

    for (auto axisIdentifier : maze->getAllAxis()) {
        Point p = Point::getNeighbourPoint(workingPoint, axisIdentifier, Point::positive);
        potentialPoints.push_back(p);
    }

    maze->connectNodes(workingPoint, maze->getRandomPointFromVector(potentialPoints));

    //Foreach axis
        //Get neighbouring points on that axis identified by positive and negative
            //For each positive point
                //insert as viable candidate
        //Pick random from viable candidates
            //connectNodes
        //Pick from viable candidates
            //set current node as it.

}

int main(int argc, char **argv) {

    opengl graphics(argc, argv, render);

    Maze maze;

    for (int x=-3; x<3; x++) {
        for (int y=-3; y<3; y++) {
            maze.createNode(create2DPoint(x, y));
        }
    }


    Maze *mazePtr = &maze;


    binaryAlgorithm(mazePtr);

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
