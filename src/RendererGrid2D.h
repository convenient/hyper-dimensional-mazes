#ifndef MAZES_FOR_PROGRAMMERS_RENDERERGRID2D_H
#define MAZES_FOR_PROGRAMMERS_RENDERERGRID2D_H

#include <unistd.h>

#include "maze.h"
#include <GL/glut.h>

class RendererGrid2D {
private:
    static void drawNode(Node *node, std::string xAxisIdentifier, std::string yAxisIdentifier) {
        GLfloat squareSize = 0.05;

        Point nodePosition = node->getPoint();

        int nodePositionX = nodePosition.getPositionOnAxis(xAxisIdentifier);
        int nodePositionY = nodePosition.getPositionOnAxis(yAxisIdentifier);

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

                int tmpNodePositionX = p.getPositionOnAxis(xAxisIdentifier);
                int tmpNodePositionY = p.getPositionOnAxis(yAxisIdentifier);

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
                    throw std::logic_error("Could not figure out how nodes are linked");
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

        //unsigned int microseconds = 30000;
        //usleep(microseconds);
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

        std::vector<std::string> axis = m->getAllAxis();

        if (axis.size() !=2) {
            throw std::logic_error("Tried to render a non-2d maze in a 2d grid renderer");
        }

        for (auto i : m->getMap()) {
            Node *node = i.second;
            drawNode(node, axis.front(), axis.back());
        }

        glutMainLoop();
    }
};


#endif //MAZES_FOR_PROGRAMMERS_RENDERERGRID2D_H
