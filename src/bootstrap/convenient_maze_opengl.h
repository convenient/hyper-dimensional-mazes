#ifndef MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_OPENGL_H
#define MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_OPENGL_H

#include "convenient_maze.h"
#include "../Renderer/RendererGrid3D.h"

bool showTextSolution = false;

namespace convenient_maze_opengl {

    void generateCallback(Maze *m, Solver *s) {
        showTextSolution = true;
        RendererText::drawNodeGoal(s->getStartNode(), s->getEndNode());
    }

    void solveCallback(Maze *m, Solver *s) {
        if (showTextSolution) {
            RendererText::drawPath(s->solve());
            showTextSolution = false;
        }
    }

    static int
    init(int argc, char **argv, Maze *mazePtr, std::string dimensions, std::string defaultLength, int microDrawDelay) {

        convenient_maze::init(argc, argv, mazePtr, dimensions, defaultLength);

        RendererGrid3D *rendererGridPtr =
                new RendererGrid3D(
                        mazePtr,
                        convenient_maze::getSolver(),
                        convenient_maze::getTitleCharStar(),
                        generateCallback,
                        solveCallback,
                        microDrawDelay
                );
        rendererGridPtr->startOpenGl();
        return 0;
    }
}

#endif //MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_OPENGL_H
