#ifndef MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_H
#define MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_H

#include <iostream>
#include <string>
#include "../lib/cxxopts/src/cxxopts.hpp"
#include "../graph/solver.h"
#include "../Renderer/RendererText.h"
#include "../lib/NestedLoop/NestedLoop.h"

namespace convenient_maze {

    cxxopts::Options opts("", "");
    Solver *solver;

    Maze *maze;
    int numberOfDimensions;

    static std::string getMazeName() {
        return maze->getName();
    }

    static std::string getTitleString() {
        return getMazeName() + " Maze - " + std::to_string(numberOfDimensions) + "D Grid";
    }

    static char *getTitleCharStar() {
        std::string titleAsString = getTitleString();

        char *title = new char[titleAsString.length() + 1];
        strcpy(title, titleAsString.c_str());
        return title;
    }

    static int getMazeLength() {
        return opts["length"].as<int>();
    }

    static Solver *getSolver() {
        return solver;
    }

    static void describeDimensions() {
        std::cout << "Generating a " + getMazeName() + " maze of ";
        for (int i = 0; i < numberOfDimensions; i++) {
            if (i > 0) {
                std::cout << " by ";
            }
            std::cout << getMazeLength();
        }
        std::cout << std::endl;
    }

    static void addNodesToMaze() {
        int mazeLength = getMazeLength();

        //Offset the node position to make rendering easier and map to nice opengl stuff.
        int minpart = (int) floor(mazeLength / 2) * -1;
        int maxpart = (int) ceil(mazeLength / 2);

        if (numberOfDimensions == 3) {
            for (int x = minpart; x < maxpart; x++) {
                for (int y = minpart; y < maxpart; y++) {
                    for (int z = minpart; z < maxpart; z++) {
                        Point p;
                        p.addPosition("x", x);
                        p.addPosition("y", y);
                        p.addPosition("z", z);
                        maze->createNode(p);
                    }
                }
            }
        } else if (numberOfDimensions == 2) {

            for (int x = minpart; x < maxpart; x++) {
                for (int y = minpart; y < maxpart; y++) {
                    Point p;
                    p.addPosition("x", x);
                    p.addPosition("y", y);
                    maze->createNode(p);
                }
            }

        } else {
            //Looper was a good movie.
            //Joseph Gordon-Levitt looked _really_ similar to Bruce Willis, it was uncanny.
            nestedLoop::nestedLoop looper(numberOfDimensions, mazeLength);

            while (looper.next()) {
                Point p;

                for (int i = 0; i < looper.idxes.size(); i++) {
                    int asciiVal = 65 + i;
                    char character = static_cast<char>(65 + i);
                    std::string charString(1, character);
                    int val = looper.idxes[i];
                    p.addPosition(charString, looper.idxes[i]);
                }
                maze->createNode(p);
            }
        }
    }

    static int init(int argc, char **argv, Maze *mazePtr, std::string dimensions, std::string defaultLength) {
        maze = mazePtr;

        opts.add_options()
                ("d,dimensions", "dimensions", cxxopts::value<int>()->default_value(dimensions))
                ("l,length", "edge length", cxxopts::value<int>()->default_value(defaultLength))
                ("s,seed", "maze seed", cxxopts::value<unsigned long>());
        opts.parse(argc, argv);

        if (opts.count("seed")) {
            unsigned long seed = opts["seed"].as<unsigned long>();
            mazePtr->setSeed(seed);
        }

        numberOfDimensions = opts["dimensions"].as<int>();

        std::cout << "Using seed: " << mazePtr->getSeed() << std::endl;
        describeDimensions();

        solver = new Solver(mazePtr);
        addNodesToMaze();

        return 0;
    }
}


#endif //MAZES_FOR_PROGRAMMERS_CONVENIENT_MAZE_H
