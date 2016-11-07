#include "graph/maze/mazebinary.h"
#include "bootstrap/convenient_maze.h"

int main(int argc, char **argv) {
    //Dimensions default    4
    //Edge length default   6
    //Render textonly
    return convenient_maze::init(argc, argv, new MazeBinary, "4", "6", false);
}