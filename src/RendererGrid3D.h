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
#include "solver.h"
class RendererGrid3D;
RendererGrid3D *superSecretOpenGlHackyPointer;

void processKeys(unsigned char key, int x, int y);

class RendererGrid3D {

    GLfloat squareSize = 0.03;

    GLfloat rotateMultiplier = -8;

    bool showingSolution = false;
    bool firstRenderComplete = false;
    bool rotate = false;

    GLfloat rotationXaxis = 0.0f;
    GLfloat rotationYaxis = 0.0f;
    GLfloat rotationZaxis = 0.0f;

    std::string xAxisIdentifier;
    std::string yAxisIdentifier;
    std::string zAxisIdentifier;

    bool axisInitialised = false;

    void (*generateCallback)(Maze *m, Solver *s);
    void (*solveCallback)(Maze *m, Solver *s);
    Solver *solver;

    Maze *m;

    std::vector<std::vector<float>> standardCubeColours;
    std::vector<std::vector<float>> endCubeColours;
    std::vector<std::vector<float>> startCubeColours;
    std::vector<std::vector<float>> connectorCubeColours;

    void initColours() {
        std::vector<float> orangish;
        std::vector<float> orange;
        std::vector<float> yellow;
        std::vector<float> red;
        std::vector<float> green;
        std::vector<float> grey;

        yellow.push_back(1.0f);
        yellow.push_back(1.0f);
        yellow.push_back(0.0f);

        orange.push_back(1.0f);
        orange.push_back(0.5f);
        orange.push_back(0.0f);

        orangish.push_back(1.0f);
        orangish.push_back(0.75f);
        orangish.push_back(0.0f);

        red.push_back(1.0f);
        red.push_back(0.0f);
        red.push_back(0.0f);

        green.push_back(0.0f);
        green.push_back(1.0f);
        green.push_back(0.0f);

        grey.push_back(0.5f);
        grey.push_back(0.5f);
        grey.push_back(0.5f);

        standardCubeColours.push_back(orange);
        standardCubeColours.push_back(orangish);
        standardCubeColours.push_back(yellow);

        endCubeColours.push_back(red);
        endCubeColours.push_back(red);
        endCubeColours.push_back(red);

        startCubeColours.push_back(green);
        startCubeColours.push_back(green);
        startCubeColours.push_back(green);

        connectorCubeColours.push_back(grey);
        connectorCubeColours.push_back(grey);
        connectorCubeColours.push_back(grey);

    }

    void drawMaze() {
        if (!this->axisInitialised) {
            std::vector<std::string> axis = m->getAllAxis();

            if (axis.size() == 3) {
                xAxisIdentifier = axis.at(0);
                yAxisIdentifier = axis.at(1);
                zAxisIdentifier = axis.at(2);
                this->threeDimensions = true;
            } else if (axis.size() == 2) {
                xAxisIdentifier = axis.at(0);
                yAxisIdentifier = axis.at(1);
                zAxisIdentifier = "totally_not_a_real_axis_identifier";
                this->threeDimensions = false;
            } else {
                throw std::logic_error("Tried to render a non-3d or a non-2d maze");
            }

            this->axisInitialised = true;
        }

        Node *start = nullptr;
        Node *end = nullptr;
        if (this->solver->getMazeSolved()) {
            start = solver->getStartNode();
            end = solver->getEndNode();
        }
        for (auto i : this->m->getVisitedNodesMap()) {
            Node *node = i.second;
            if (this->solver->getMazeSolved() && (node == start || node == end)) {
                continue;
            }
            drawNode(node);
        }

        if (this->solver->getMazeSolved()) {
            this->drawStartNode();
            this->drawEndNode();
        }
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

        for (auto node : path) {
            drawNode(node);
        }

        this->drawStartNode();
        this->drawEndNode();
    }

    void drawStartNode() {
        Node *start = solver->getStartNode();
        drawCube(start->getPoint(), squareSize, startCubeColours);
        drawConnectors(start);
    }

    void drawEndNode() {
        Node *end = solver->getEndNode();
        drawCube(end->getPoint(), squareSize, endCubeColours);
        drawConnectors(end);
    }

    void drawNode(Node *node) {
        Point nodePosition = node->getPoint();

        /**
         * Paint node for debugging purposes
         */
        Point test;
        /*test.addPosition("x", 0);
        test.addPosition("y", 0);
        test.addPosition("z", -1);*/

        Point test1;
        /*test1.addPosition("x", 0);
        test1.addPosition("y", -1);
        test1.addPosition("z", -1);*/

        std::vector<std::vector<float>> drawColours = standardCubeColours;

        if (test.getAsString() == nodePosition.getAsString()) {
            drawColours = endCubeColours;
        } else if (test1.getAsString() == nodePosition.getAsString()) {
            drawColours = startCubeColours;
        }

        drawCube(nodePosition, squareSize, drawColours);
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

        GLfloat connectorCubeSize = squareSize/4.0f;
        if (isLinkedXPos) {
            drawCube(nodePosition, connectorCubeSize, connectorCubeColours, true, xAxisIdentifier, +1);
        }
        if (isLinkedXNeg) {
            drawCube(nodePosition, connectorCubeSize, connectorCubeColours, true, xAxisIdentifier, -1);
        }
        if (isLinkedYPos) {
            drawCube(nodePosition, connectorCubeSize, connectorCubeColours, true, yAxisIdentifier, +1);
        }
        if (isLinkedYNeg) {
            drawCube(nodePosition, connectorCubeSize, connectorCubeColours, true, yAxisIdentifier, -1);
        }
        if (isLinkedZPos) {
            drawCube(nodePosition, connectorCubeSize, connectorCubeColours, true, zAxisIdentifier, +1);
        }
        if (isLinkedZNeg) {
            drawCube(nodePosition, connectorCubeSize, connectorCubeColours, true, zAxisIdentifier, -1);
        }
    }

    void drawCube(Point p, GLfloat size, std::vector<std::vector<float>> colours, bool connector = false, std::string connectorAxisIdentifier = "", int connectorOffset = 0) {

        float colour1A = colours.at(0).at(0);
        float colour1B = colours.at(0).at(1);
        float colour1C = colours.at(0).at(2);

        float colour2A = colours.at(1).at(0);
        float colour2B = colours.at(1).at(1);
        float colour2C = colours.at(1).at(2);

        float colour3A = colours.at(2).at(0);
        float colour3B = colours.at(2).at(1);
        float colour3C = colours.at(2).at(2);

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

        glBegin(GL_QUADS);

        // Back face (z = -1.0f)
        glColor3f(colour1A, colour1B, colour1C);
        glVertex3f( size +xOffset, -size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset,  size +yOffset, -size +zOffset);
        glVertex3f( size +xOffset,  size +yOffset, -size +zOffset);

        // Front face  (z = 1.0f)
        glVertex3f( size +xOffset,  size +yOffset, size +zOffset);
        glVertex3f(-size +xOffset,  size +yOffset, size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset, size +zOffset);
        glVertex3f( size +xOffset, -size +yOffset, size +zOffset);

        // Top face (y = 1.0f)
        glColor3f(colour2A, colour2B, colour2C);
        glVertex3f( size +xOffset, size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset, size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset, size +yOffset,  size +zOffset);
        glVertex3f( size +xOffset, size +yOffset,  size +zOffset);

        // Bottom face (y = -1.0f)
        glVertex3f( size +xOffset, -size +yOffset,  size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset,  size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset, -size +zOffset);
        glVertex3f( size +xOffset, -size +yOffset, -size +zOffset);

        // Left face (x = -1.0f)
        glColor3f(colour3A, colour3B, colour3C);
        glVertex3f(-size +xOffset,  size +yOffset,  size +zOffset);
        glVertex3f(-size +xOffset,  size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset, -size +zOffset);
        glVertex3f(-size +xOffset, -size +yOffset,  size +zOffset);

        // Right face (x = 1.0f)
        glVertex3f(size +xOffset,  size +yOffset, -size +zOffset);
        glVertex3f(size +xOffset,  size +yOffset,  size +zOffset);
        glVertex3f(size +xOffset, -size +yOffset,  size +zOffset);
        glVertex3f(size +xOffset, -size +yOffset, -size +zOffset);
        glEnd();
    }

    static void linkCallback(Maze *m, Node *a, Node *b) {

        if (superSecretOpenGlHackyPointer->threeDimensions) {
            unsigned long count = superSecretOpenGlHackyPointer->m->getMap().size();
            unsigned long interval = count / 100;
            if (superSecretOpenGlHackyPointer->threeDimensionRotateCount % interval == 0) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                superSecretOpenGlHackyPointer->rotationXaxis += (0.075f) * superSecretOpenGlHackyPointer->rotateMultiplier;
                superSecretOpenGlHackyPointer->rotationYaxis += (0.05f) * superSecretOpenGlHackyPointer->rotateMultiplier;

                glRotatef(superSecretOpenGlHackyPointer->rotationXaxis, 1.0f, 0.0f, 0.0f);
                glRotatef(superSecretOpenGlHackyPointer->rotationYaxis, 0.0f, 1.0f, 0.0f);
                glRotatef(superSecretOpenGlHackyPointer->rotationZaxis, 0.0f, 0.0f, 1.0f);
            }
            superSecretOpenGlHackyPointer->threeDimensionRotateCount++;
        }

        superSecretOpenGlHackyPointer->drawMaze();

        glutPostRedisplay();
        glFlush();//probably overkill, but it works.
    }

    static void processKeys(unsigned char key, int x, int y)
    {
        unsigned char charKey = tolower(key);

        switch (key)
        {
            case 'q':
                exit(0);
                break;
            case 'g':
                superSecretOpenGlHackyPointer->generateAndDraw();
                break;
            case 's':
                if (superSecretOpenGlHackyPointer->showingSolution) {
                    superSecretOpenGlHackyPointer->showingSolution = false;
                } else {
                    superSecretOpenGlHackyPointer->showingSolution = true;
                }
                glutPostRedisplay();
                break;
            case 'p':
                superSecretOpenGlHackyPointer->rotateMultiplier+=1;
                break;
            case 'o':
                superSecretOpenGlHackyPointer->rotateMultiplier-=1;
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
            GLfloat multiplier = superSecretOpenGlHackyPointer->rotateMultiplier;

            /* Rotate Cube */
            superSecretOpenGlHackyPointer->rotationXaxis += 0.075f * multiplier;
            superSecretOpenGlHackyPointer->rotationYaxis += 0.05f * multiplier;

            glutPostRedisplay();
        } else if (!superSecretOpenGlHackyPointer->firstRenderComplete) {
            superSecretOpenGlHackyPointer->generate();
            superSecretOpenGlHackyPointer->solver->solve();
            superSecretOpenGlHackyPointer->firstRenderComplete = true;
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

        if (superSecretOpenGlHackyPointer->showingSolution) {
            superSecretOpenGlHackyPointer->solve();
        } else {
            superSecretOpenGlHackyPointer->drawMaze();
        }

        glFlush();
    }

public:

    bool threeDimensions = false;
    unsigned long threeDimensionRotateCount = 0;

    void generate() {
        m->generate();
    }

    void generateAndDraw() {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m->generate();
        solver->setMazeUnsolved();
        std::vector<Node *> solution = solver->solve();

        this->drawMaze();

        this->generateCallback(m, solver);
        glutPostRedisplay();
    }

    void solve() {
        std::vector<Node *> solution = this->solver->solve();
        this->drawPath(solution);
        this->solveCallback(m, this->solver);
    }

    RendererGrid3D (Maze *maze, Solver *solver, char *title, void (*generateCallbackFunc)(Maze *m, Solver *s), void (*solveCallbackFunc)(Maze *m, Solver *s)) {

        this->m = maze;
        this->m->registerCallbackLinkNodes(this->linkCallback);

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

        initColours();

        superSecretOpenGlHackyPointer = this;
    }

    void startOpenGl() {
        glutMainLoop();
    }
};




#endif //MAZES_FOR_PROGRAMMERS_RENDERERGRID3D_H
