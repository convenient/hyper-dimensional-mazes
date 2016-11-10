#ifndef MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_TEXTONLY_H
#define MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_TEXTONLY_H

#include "convenient_maze.h"

namespace convenient_maze_textonly {
    static int init(int argc, char **argv, Maze *mazePtr, std::string dimensions, std::string defaultLength) {
        convenient_maze::init(argc, argv, mazePtr, dimensions, defaultLength);

        mazePtr->generate();
        std::vector<Node *> path = convenient_maze::getSolver()->solve();
        RendererText::drawPath(path);

        return 0;
    }
}

#endif //MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_TEXTONLY_H
