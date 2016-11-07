#ifndef MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_H
#define MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_H

#include <iostream>
#include <string>
#include "../lib/cxxopts/src/cxxopts.hpp"
#include "../graph/solver.h"
#include "../renderer/RendererText.h"
#include "../renderer/RendererGrid3D.h"

bool showTextSolution = false;

//todo can these be namespaced?
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

namespace convenient_maze {

    cxxopts::Options opts("", "");

    Maze *maze;
    int numberOfDimensions;

    static std::string getMazeName() {
        return maze->getName();
    }

    static std::string getTitleString() {
        return getMazeName() + " Maze - " + std::to_string(numberOfDimensions) + "D Grid";
    }

    static char * getTitleCharStar() {
        std::string titleAsString = getTitleString();

        char *title = new char[titleAsString.length() + 1];
        strcpy(title, titleAsString.c_str());
        return title;
    }

    static int getMazeLength() {
        return opts["length"].as<int>();
    }

    static void describeDimensions() {
        std::cout << "Generating a " + getMazeName() + " maze of ";
        for (int i=0; i<numberOfDimensions; i++) {
            if (i>0) {
                std::cout << " by ";
            }
            std::cout << getMazeLength();
        }
        std::cout << std::endl;
    }

    static void addNodesToMaze() {
        int mazeLength = getMazeLength();

        //Offset the node position to make rendering easier and map to nice opengl stuff.
        int minpart = (int)floor(mazeLength/2) * -1;
        int maxpart = (int)ceil(mazeLength/2);

        if (numberOfDimensions == 3) {
            for (int x=minpart; x<maxpart; x++) {
                for (int y=minpart; y<maxpart; y++) {
                    for (int z=minpart; z<maxpart; z++) {
                        Point p;
                        p.addPosition("x", x);
                        p.addPosition("y", y);
                        p.addPosition("z", z);
                        maze->createNode(p);
                    }
                }
            }
        } else if (numberOfDimensions == 2) {

            for (int x=minpart; x<maxpart; x++) {
                for (int y=minpart; y<maxpart; y++) {
                    Point p;
                    p.addPosition("x", x);
                    p.addPosition("y", y);
                    maze->createNode(p);
                }
            }

        } else if (numberOfDimensions == 4) {
            for (int w=0; w< mazeLength; w++) {
                for (int x = 0; x < mazeLength; x++) {
                    for (int y = 0; y < mazeLength; y++) {
                        for (int z = 0; z < mazeLength; z++) {
                            Point p;
                            p.addPosition("w", w);
                            p.addPosition("x", x);
                            p.addPosition("y", y);
                            p.addPosition("z", z);
                            maze->createNode(p);
                        }
                    }
                }
            }
        } else {
            //todo make this do some fun recursive stuff
            throw std::logic_error("Need to sort this handler out... n dimensions not fully sorted");
        }
    }

    static int init(int argc, char **argv, Maze *mazePtr, std::string dimensions, std::string defaultLength, bool shouldRender) {
        maze = mazePtr;

        opts.add_options()
                ("d,dimensions", "dimensions", cxxopts::value<int>()->default_value(dimensions))
                ("l,length", "edge length", cxxopts::value<int>()->default_value(defaultLength))
                ("s,seed", "maze seed", cxxopts::value<unsigned long>())
                ;
        opts.parse(argc, argv);

        if (opts.count("seed")) {
            unsigned long seed = opts["seed"].as<unsigned long>();
            mazePtr->setSeed(seed);
        }

        numberOfDimensions = opts["dimensions"].as<int>();

        std::cout << "Using seed: " << mazePtr->getSeed() << std::endl;
        describeDimensions();

        Solver *solver = new Solver(mazePtr);
        addNodesToMaze();

        if (shouldRender) {
            RendererGrid3D *rendererGridPtr =
                    new RendererGrid3D(
                            mazePtr,
                            solver,
                            getTitleCharStar(),
                            generateCallback,
                            solveCallback
                    );
            rendererGridPtr->startOpenGl();
        } else {
            mazePtr->generate();
            std::vector<Node *> path = solver->solve();
            RendererText::drawPath(path);
        }

        return 0;
    }
}


#endif //MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_H
