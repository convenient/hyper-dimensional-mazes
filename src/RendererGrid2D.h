#ifndef MAZES_FOR_PROGRAMMERS_RENDERERGRID2D_H
#define MAZES_FOR_PROGRAMMERS_RENDERERGRID2D_H

#include <unistd.h>

#include "maze.h"
#include <GL/glut.h>

class RendererGrid2D {
private:
    static void drawNode(Node *node) {
        GLfloat squareSize = 0.05;

        Point nodePosition = node->getPoint();

        //TODO Make this node stuff generic and magical
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

        unsigned int microseconds = 30000;
        usleep(microseconds);
    }

public:
    static void render(Maze *m, char *title, void (*renderFunction)(void)) {

        char fakeParam[] = "fake";
        char *fakeargv[] = {fakeParam, NULL};
        int fakeargc = 1;

        glutInit(&fakeargc, fakeargv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
        glutInitWindowSize(600, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow(title);
        glutDisplayFunc(renderFunction);


        //Grey background
        glClearColor(0.75, 0.75, 0.75, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();

        for (auto i : m->getMap()) {
            Node *node = i.second;
            drawNode(node);
        }

        glutMainLoop();
    }
};


#endif //MAZES_FOR_PROGRAMMERS_RENDERERGRID2D_H
