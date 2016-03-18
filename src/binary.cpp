#include "twodimensionalmaze.h"

#include "opengl.h"

using namespace std;

void drawSquare(int x, int y) {
    GLfloat squareSize = 0.1;

    GLfloat xOffset = squareSize * x;
    GLfloat yOffset = squareSize * y;

    glBegin(GL_LINES);
    //Horizontal line bottom
    glVertex2f(squareSize + xOffset, yOffset);
    glVertex2f(xOffset, yOffset);

    //Vertical line left
    glVertex2f(xOffset, yOffset);
    glVertex2f(xOffset, squareSize + yOffset);

    //Horizontal line top
    glVertex2f(squareSize + xOffset, squareSize + yOffset);
    glVertex2f(xOffset, squareSize + yOffset);

    //Vertical line right
    glVertex2f(squareSize + xOffset, squareSize + yOffset);
    glVertex2f(squareSize + xOffset, yOffset);

    glEnd();
    glFlush();
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

    //Grey background
    glClearColor(0.75, 0.75, 0.75, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    for (auto i : maze.getMap()) {
        TwoDimensionalNode *node = i.second;
        int x = node->getX();
        int y = node->getY();
        drawSquare(x, y);
    }


    graphics.startLoop();
    return 0;
}
