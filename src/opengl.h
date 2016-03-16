#ifndef MAZES_FOR_PROGRAMMERS_OPENGL_H
#define MAZES_FOR_PROGRAMMERS_OPENGL_H

#include <GL/glut.h>

class opengl {

public:
    opengl(int argcs, char **argvs, void (*renderFunctio)(void)) {
        glutInit(&argcs, argvs);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(300, 300);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Hello world :D");
        glutDisplayFunc(renderFunctio);
    }

public:
    void startLoop(void) {
        glutMainLoop();
    }
};


#endif //MAZES_FOR_PROGRAMMERS_OPENGL_H
