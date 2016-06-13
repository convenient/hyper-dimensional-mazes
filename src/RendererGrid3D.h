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

    GLfloat squareSize = 0.05;
    GLfloat markerSize = 0.03;

    GLdouble eyeX = 0;
    GLdouble eyeY = 0;
    GLdouble eyeZ = 0;

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

            if (axis.size() !=3) {
                throw std::logic_error("Tried to render a non-3d maze in a 3d grid renderer");
            }

            xAxisIdentifier = axis.at(0);
            yAxisIdentifier = axis.at(1);
            zAxisIdentifier = axis.at(2);

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

        glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
        // Top face (y = 1.0f)
        // Define vertices in counter-clockwise (CCW) order with normal pointing out
        glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f( squareSize, squareSize, -squareSize);
        glVertex3f(-squareSize, squareSize, -squareSize);
        glVertex3f(-squareSize, squareSize,  squareSize);
        glVertex3f( squareSize, squareSize,  squareSize);

        // Bottom face (y = -1.0f)
        glColor3f(1.0f, 0.5f, 0.0f);     // Orange
        glVertex3f( squareSize, -squareSize,  squareSize);
        glVertex3f(-squareSize, -squareSize,  squareSize);
        glVertex3f(-squareSize, -squareSize, -squareSize);
        glVertex3f( squareSize, -squareSize, -squareSize);

        // Front face  (z = 1.0f)
        glColor3f(1.0f, 0.0f, 0.0f);     // Red
        glVertex3f( squareSize,  squareSize, squareSize);
        glVertex3f(-squareSize,  squareSize, squareSize);
        glVertex3f(-squareSize, -squareSize, squareSize);
        glVertex3f( squareSize, -squareSize, squareSize);

        // Back face (z = -1.0f)
        glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
        glVertex3f( squareSize, -squareSize, -squareSize);
        glVertex3f(-squareSize, -squareSize, -squareSize);
        glVertex3f(-squareSize,  squareSize, -squareSize);
        glVertex3f( squareSize,  squareSize, -squareSize);

        // Left face (x = -1.0f)
        glColor3f(0.0f, 0.0f, 1.0f);     // Blue
        glVertex3f(-squareSize,  squareSize,  squareSize);
        glVertex3f(-squareSize,  squareSize, -squareSize);
        glVertex3f(-squareSize, -squareSize, -squareSize);
        glVertex3f(-squareSize, -squareSize,  squareSize);

        // Right face (x = 1.0f)
        glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
        glVertex3f(squareSize,  squareSize, -squareSize);
        glVertex3f(squareSize,  squareSize,  squareSize);
        glVertex3f(squareSize, -squareSize,  squareSize);
        glVertex3f(squareSize, -squareSize, -squareSize);
        glEnd();  // End of drawing color-cube

        glFlush();

    }

    static void processKeys(unsigned char key, int x, int y)
    {
        unsigned char charKey = tolower(key);

        GLdouble size = 0.5;

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
            case 'i':
                superSecretOpenGlHackyPointer->eyeX+=size;
            case 'o':
                superSecretOpenGlHackyPointer->eyeY+=size;
            case 'p':
                superSecretOpenGlHackyPointer->eyeZ+=size;
            case 'b':
                superSecretOpenGlHackyPointer->eyeX-=size;
            case 'n':
                superSecretOpenGlHackyPointer->eyeY-=size;
            case 'm':
                superSecretOpenGlHackyPointer->eyeZ-=size;
            default:
                break;
        }


        std::cout << "resetting gluLookAt" << std::endl;
        gluLookAt(0, 0, 0,
                  0, 0,-1,
                  0, 1, 0);
        glEnd(); /// !!!!!! replaced glFlush
        glutSwapBuffers();
    }

    static void render() {

    }

public:

    void generate() {
//        m->generate();

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
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
        glutInitWindowSize(600, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow(title);
        glutDisplayFunc(&render);
        glutKeyboardFunc(&processKeys);

        generateCallback = generateCallbackFunc;
        solveCallback = solveCallbackFunc;

        superSecretOpenGlHackyPointer = this;

        gluLookAt(0, 0.5, 0,
                  0, 0,-1,
                  0, 1, 0);
    }

    void startOpenGl() {
        glutMainLoop();
    }
};




#endif //MAZES_FOR_PROGRAMMERS_RENDERERGRID3D_H
