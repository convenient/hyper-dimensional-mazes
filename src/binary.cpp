#include "twodimensionalmaze.h"

#include "opengl.h"

#include <unistd.h>

using namespace std;

void drawNode(TwoDimensionalNode *node) {
    GLfloat squareSize = 0.1;

    GLfloat xOffset = squareSize * node->getX();
    GLfloat yOffset = squareSize * node->getY();

    glBegin(GL_LINES);

    if (node->getDownPtr() == nullptr) {
        //Horizontal line bottom
        glVertex2f(squareSize + xOffset, yOffset);
        glVertex2f(xOffset, yOffset);
    }

    //Vertical line left
    glVertex2f(xOffset, yOffset);
    glVertex2f(xOffset, squareSize + yOffset);

    //Horizontal line top
    if (node->getUpPtr() == nullptr) {
        glVertex2f(squareSize + xOffset, squareSize + yOffset);
        glVertex2f(xOffset, squareSize + yOffset);
    }

    //Vertical line right
    glVertex2f(squareSize + xOffset, squareSize + yOffset);
    glVertex2f(squareSize + xOffset, yOffset);

    glEnd();
    glFlush();

//    unsigned int microseconds = 2000000;
//    usleep(microseconds);
}

void render() {

}

int main(int argc, char **argv) {

    opengl graphics(argc, argv, render);

    TwoDimensionalMaze maze;

    maze.createNode(0, 0);
    maze.createNode(0, 1);
    maze.createNode(1, 0);
    maze.createNode(1, 1);

    maze.connectNodes(0, 0, 0, 1);

    //Grey background
    glClearColor(0.75, 0.75, 0.75, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    for (auto i : maze.getMap()) {
        TwoDimensionalNode *node = i.second;
        drawNode(node);
    }

    graphics.startLoop();
    return 0;
}
