#ifndef MAZES_FOR_PROGRAMMERS_RENDERERGRID2D_H
#define MAZES_FOR_PROGRAMMERS_RENDERERGRID2D_H

#include <unistd.h>

#ifdef __APPLE__
#include <OpenGL/gl.h> 
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "maze.h"

class RendererGrid2D {
    Maze *m;

    GLfloat squareSize = 0.05;
    GLfloat markerSize = 0.03;

    std::string xAxisIdentifier;
    std::string yAxisIdentifier;

    bool axisInitialised = false;

public:

    void drawMaze() {
        if (!this->axisInitialised) {
            std::vector<std::string> axis = m->getAllAxis();

            if (axis.size() !=2) {
                throw std::logic_error("Tried to render a non-2d maze in a 2d grid renderer");
            }

            xAxisIdentifier = axis.front();
            yAxisIdentifier = axis.back();
            this->axisInitialised = true;
        }

        //Grey background
        glClearColor(0.75, 0.75, 0.75, 1);
        glColor3f(0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto i : this->m->getMap()) {
            Node *node = i.second;
            drawNode(node);
        }

        glFlush();
    }

    /**
     * Draw the path between the first and last node.
     */
    void drawPath(std::vector<Node *> path) {

        if (path.size() <=2) {
            return;
        }

        path.erase(path.begin());
        path.erase(path.end() -1);

        glColor3f(1.0, 0.5, 0.0);
        for (auto node : path) {
            drawMarker(node->getPoint());
        }

        glFlush();
    }

    void drawStartNode(Node *node) {
        glColor3f(0.0, 1.0, 0.0);
        drawMarker(node->getPoint());
        glFlush();
    }

    void drawEndNode(Node *node) {
        glColor3f(1.0, 0.0, 0.0);
        drawMarker(node->getPoint());
        glFlush();
    }

    void drawMarker(Point p) {
        GLfloat differenceSize = squareSize - markerSize;

        GLfloat xOffset = squareSize * p.getPositionOnAxis(xAxisIdentifier);
        GLfloat yOffset = squareSize * p.getPositionOnAxis(yAxisIdentifier);

        glBegin(GL_POLYGON);
        glVertex3f(markerSize - differenceSize + xOffset, markerSize - differenceSize + yOffset, 0.0);
        glVertex3f(markerSize*2 - differenceSize + xOffset, markerSize - differenceSize + yOffset, 0.0);
        glVertex3f(markerSize*2 - differenceSize + xOffset, markerSize*2 - differenceSize + yOffset, 0.0);
        glVertex3f(markerSize - differenceSize + xOffset, markerSize*2 - differenceSize + yOffset, 0.0);
        glEnd();
    }

    void drawNode(Node *node) {

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
    }

    RendererGrid2D (Maze *maze, char *title, void (*renderFunc)(void), void (*keysFunc)(unsigned char key, int x, int y)) {

        this->m = maze;

        char fakeParam[] = "fake";
        char *fakeargv[] = {fakeParam, NULL};
        int fakeargc = 1;

        glutInit(&fakeargc, fakeargv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
        glutInitWindowSize(600, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow(title);
        glutDisplayFunc(renderFunc);
        glutKeyboardFunc(keysFunc);
    }

    void startOpenGl() {
        glutMainLoop();
    }
};


#endif //MAZES_FOR_PROGRAMMERS_RENDERERGRID2D_H
