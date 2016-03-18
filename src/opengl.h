#ifndef MAZES_FOR_PROGRAMMERS_OPENGL_H
#define MAZES_FOR_PROGRAMMERS_OPENGL_H

#include <GL/glut.h>

class opengl {

public:
    opengl(int argcs, char **argvs, void (*renderFunction)(void)) {
        glutInit(&argcs, argvs);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_ALPHA);
        glutInitWindowSize(300, 300);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Hello world :D");
        glutDisplayFunc(renderFunction);
    }

public:
    void startLoop(void) {
        glutMainLoop();
    }
};


#endif //MAZES_FOR_PROGRAMMERS_OPENGL_H
