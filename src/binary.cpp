#include "maze.h"
#include "opengl.h"

#include <unistd.h>

using namespace std;

void drawNode(Node *node) {
    GLfloat squareSize = 0.1;

    Point p = node->getPoint();

    GLfloat xOffset = squareSize * p.getPositionOnAxis("x");
    GLfloat yOffset = squareSize * p.getPositionOnAxis("y");

    glBegin(GL_LINES);

//    if (node->getDownPtr() == nullptr) {
        //Horizontal line bottom
        glVertex2f(squareSize + xOffset, yOffset);
        glVertex2f(xOffset, yOffset);
//    }

    //Vertical line left
    glVertex2f(xOffset, yOffset);
    glVertex2f(xOffset, squareSize + yOffset);

    //Horizontal line top
//    if (node->getUpPtr() == nullptr) {
        glVertex2f(squareSize + xOffset, squareSize + yOffset);
        glVertex2f(xOffset, squareSize + yOffset);
//    }

    //Vertical line right
    glVertex2f(squareSize + xOffset, squareSize + yOffset);
    glVertex2f(squareSize + xOffset, yOffset);

    glEnd();
    glFlush();
//
    unsigned int microseconds = 2000000;
    usleep(microseconds);
}

void render() {

}

Point create2DPoint(int x, int y) {
    Point p;
    p.addPoint("x", x);
    p.addPoint("y", y);
    return p;
}

int main(int argc, char **argv) {

    opengl graphics(argc, argv, render);

    Maze maze;

    Node* a = maze.createNode(create2DPoint(0, 0));
    Node* b = maze.createNode(create2DPoint(0, 1));
    Node* c = maze.createNode(create2DPoint(1, 0));
    Node* d = maze.createNode(create2DPoint(1, 1));

    maze.connectNodes(a, b);

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
