#ifndef MAZES_FOR_PROGRAMMERS_RENDERERGRID3D_H
#define MAZES_FOR_PROGRAMMERS_RENDERERGRID3D_H

#include <unistd.h>

#ifdef __APPLE__
#include <OpenGL/gl.h> 
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "maze.h"
#include "Solver.h"
class RendererGrid3D;
RendererGrid3D *superSecretOpenGlHackyPointer;

void processKeys(unsigned char key, int x, int y);

class RendererGrid3D {

    GLfloat squareSize = 0.06;
    GLfloat markerSize = 0.03;

    bool rotate = false;

    GLfloat rotationXaxis;
    GLfloat rotationYaxis;
    GLfloat rotationZaxis;

    std::string xAxisIdentifier;
    std::string yAxisIdentifier;
    std::string zAxisIdentifier;

    bool axisInitialised = false;

    void (*generateCallback)(Maze *m, Solver *s);
    void (*solveCallback)(Maze *m, Solver *s);
    Solver *solver;

    Maze *m;

    void drawMaze() {
        if (!this->axisInitialised) {
            std::vector<std::string> axis = m->getAllAxis();

            if (axis.size() == 3) {
                xAxisIdentifier = axis.at(0);
                yAxisIdentifier = axis.at(1);
                zAxisIdentifier = axis.at(2);
            } else if (axis.size() == 2) {
                xAxisIdentifier = axis.at(0);
                yAxisIdentifier = axis.at(1);
                zAxisIdentifier = "totally_not_a_real_axis_identifier";
            } else {
                throw std::logic_error("Tried to render a non-3d or a non-3d maze");
            }

            this->axisInitialised = true;
        }

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
        drawCube(nodePosition, squareSize);
        drawConnectors(node);
    }

    void drawConnectors(Node *node) {

        Point nodePosition = node->getPoint();
        int nodePositionX = nodePosition.getPositionOnAxis(xAxisIdentifier);
        int nodePositionY = nodePosition.getPositionOnAxis(yAxisIdentifier);
        int nodePositionZ = nodePosition.getPositionOnAxis(zAxisIdentifier);

        bool isLinkedXPos = false;
        bool isLinkedXNeg = false;
        bool isLinkedYPos = false;
        bool isLinkedYNeg = false;
        bool isLinkedZPos = false;
        bool isLinkedZNeg = false;

        //Foreach point adjacent to the current node
        std::vector<Point> neighbouringPoints = nodePosition.getNeighbouringPoints();
        for (auto p : neighbouringPoints) {
            if (node->isLinked(p)) {
                int tmpNodePositionX = p.getPositionOnAxis(xAxisIdentifier);
                int tmpNodePositionY = p.getPositionOnAxis(yAxisIdentifier);
                int tmpNodePositionZ = p.getPositionOnAxis(zAxisIdentifier);

                bool xSame = tmpNodePositionX == nodePositionX;
                bool ySame = tmpNodePositionY == nodePositionY;
                bool zSame = tmpNodePositionZ == nodePositionZ;

                if (xSame && zSame) {
                    if (tmpNodePositionY > nodePositionY) {
                        isLinkedYPos = true;
                    } else if (tmpNodePositionY < nodePositionY) {
                        isLinkedYNeg = true;
                    }
                }

                if (ySame && zSame) {
                    if (tmpNodePositionX > nodePositionX) {
                        isLinkedXPos = true;
                    } else if (tmpNodePositionX < nodePositionX) {
                        isLinkedXNeg = true;
                    }
                }

                if (xSame && ySame) {
                    if (tmpNodePositionZ > nodePositionZ) {
                        isLinkedZPos = true;
                    } else if (tmpNodePositionZ < nodePositionZ) {
                        isLinkedZNeg = true;
                    }
                }

            }
        }

        GLfloat connectorCubeSize = squareSize/2;
        if (isLinkedXPos) {
            drawCube(nodePosition, connectorCubeSize, true, xAxisIdentifier, +1);
        }
        if (isLinkedXNeg) {
            drawCube(nodePosition, connectorCubeSize, true, xAxisIdentifier, -1);
        }
        if (isLinkedYPos) {
            drawCube(nodePosition, connectorCubeSize, true, yAxisIdentifier, +1);
        }
        if (isLinkedYNeg) {
            drawCube(nodePosition, connectorCubeSize, true, yAxisIdentifier, -1);
        }
        if (isLinkedZPos) {
            drawCube(nodePosition, connectorCubeSize, true, zAxisIdentifier, +1);
        }
        if (isLinkedZNeg) {
            drawCube(nodePosition, connectorCubeSize, true, zAxisIdentifier, -1);
        }
    }

    void drawCube(Point p, GLfloat size, bool connector = false, std::string connectorAxisIdentifier = "", int connectorOffset = 0) {

        //*1 will make the cubes intersect
        //*2 would make the cubes side by side with no buffer
        //*3 will make them have a distance of half a cube from eachother
        GLfloat xOffset = squareSize * p.getPositionOnAxis(xAxisIdentifier) * 3;
        GLfloat yOffset = squareSize * p.getPositionOnAxis(yAxisIdentifier) * 3;
        GLfloat zOffset = squareSize * p.getPositionOnAxis(zAxisIdentifier) * 3;

        if (connector) {
            if (connectorAxisIdentifier == yAxisIdentifier) {
                yOffset += connectorOffset * squareSize;
                yOffset += connectorOffset * size;
            }

            if (connectorAxisIdentifier == xAxisIdentifier) {
                xOffset += connectorOffset * squareSize;
                xOffset += connectorOffset * size;
            }

            if (connectorAxisIdentifier == zAxisIdentifier) {
                zOffset += connectorOffset * squareSize;
                zOffset += connectorOffset * size;
            }
        }

//        glBegin(GL_POLYGON);
//
//        glColor3f( 1.0, 0.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
//        glColor3f( 0.0, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
//        glColor3f( 0.0, 0.0, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
//        glColor3f( 1.0, 0.0, 1.0 );     glVertex3f( -0.5, -0.5, -0.5 );      // P4 is purple
//
//        glEnd();


        glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f( size +xOffset, size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset, size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset, size +yOffset,  size +zOffset);
        glVertex3f( size +xOffset, size +yOffset,  size +zOffset);

        // Bottom face (y = -1.0f)
        glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glVertex3f( size +xOffset, -size +yOffset,  size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset,  size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset, -size +zOffset);
        glVertex3f( size +xOffset, -size +yOffset, -size +zOffset);

        // Front face  (z = 1.0f)
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f( size +xOffset,  size +yOffset, size +zOffset);
        glVertex3f(-size +xOffset,  size +yOffset, size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset, size +zOffset);
        glVertex3f( size +xOffset, -size +yOffset, size +zOffset);

        // Back face (z = -1.0f)
        glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glVertex3f( size +xOffset, -size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset,  size +yOffset, -size +zOffset);
        glVertex3f( size +xOffset,  size +yOffset, -size +zOffset);

        // Left face (x = -1.0f)
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(-size +xOffset,  size +yOffset,  size +zOffset);
        glVertex3f(-size +xOffset,  size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset,  size +zOffset);

        // Right face (x = 1.0f)
        glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glVertex3f(size +xOffset,  size +yOffset, -size +zOffset);
        glVertex3f(size +xOffset,  size +yOffset,  size +zOffset);
        glVertex3f(size +xOffset, -size +yOffset,  size +zOffset);
        glVertex3f(size +xOffset, -size +yOffset, -size +zOffset);
        glEnd();  // End of drawing color-cube
    }


    static void processKeys(unsigned char key, int x, int y)
    {
        unsigned char charKey = tolower(key);

        GLdouble size = 0.01;

        switch (charKey)
        {
            case 'q':
                exit(0);
                break;
            case 'g':
                superSecretOpenGlHackyPointer->generate();
                break;
            case 's':
                superSecretOpenGlHackyPointer->solve();
                break;
            case 'r':
                if (superSecretOpenGlHackyPointer->rotate) {
                    superSecretOpenGlHackyPointer->rotate = false;
                } else {
                    superSecretOpenGlHackyPointer->rotate = true;
                }
                break;
            default:
                break;
        }
    }

    static void idleFunction() {
        if (superSecretOpenGlHackyPointer->rotate) {
            /* Rotate Cube */
            superSecretOpenGlHackyPointer->rotationXaxis += 0.075f;
            superSecretOpenGlHackyPointer->rotationYaxis += 0.05f;

            glutPostRedisplay();
        }
    }

    static void render() {
        //Grey background
        glColor3f(0.0, 0.0, 0.0);
        glClearColor(0.75, 0.75, 0.75, 1);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glEnable(GL_DEPTH_TEST);

        glRotatef(superSecretOpenGlHackyPointer->rotationXaxis, 1.0f, 0.0f, 0.0f);
        glRotatef(superSecretOpenGlHackyPointer->rotationYaxis, 0.0f, 1.0f, 0.0f);
        glRotatef(superSecretOpenGlHackyPointer->rotationZaxis, 0.0f, 0.0f, 1.0f);

        superSecretOpenGlHackyPointer->drawMaze();
    }

public:

    void generate() {
        m->generate();

//        solver->setMazeUnsolved();
//        std::vector<Node *> solution = solver->solve();

        this->drawMaze();

//        this->drawStartNode(solver->getStartNode());
//        this->drawEndNode(solver->getEndNode());
//
//        this->generateCallback(m, solver);
    }

    void solve() {
        std::vector<Node *> solution = this->solver->solve();
        this->drawPath(solution);
        this->solveCallback(m, this->solver);
    }

    RendererGrid3D (Maze *maze, Solver *solver, char *title, void (*generateCallbackFunc)(Maze *m, Solver *s), void (*solveCallbackFunc)(Maze *m, Solver *s)) {

        this->m = maze;
        this->solver = solver;

        char fakeParam[] = "fake";
        char *fakeargv[] = {fakeParam, NULL};
        int fakeargc = 1;

        glutInit(&fakeargc, fakeargv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
        glutInitWindowSize(600, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow(title);
        glutDisplayFunc(&render);
        glutKeyboardFunc(&processKeys);
        glutIdleFunc(&idleFunction);
        generateCallback = generateCallbackFunc;
        solveCallback = solveCallbackFunc;

        superSecretOpenGlHackyPointer = this;
    }

    void startOpenGl() {
        glutMainLoop();
    }
};




#endif //MAZES_FOR_PROGRAMMERS_RENDERERGRID3D_H
