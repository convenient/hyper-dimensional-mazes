#include "graph/maze/mazealdousbroder.h"
#include "bootstrap/convenient_maze.h"

int main(int argc, char **argv) {
    //Dimensions default    4
    //Edge length default   6
    //Render textonly
    return convenient_maze::init(argc, argv, new MazeAldousBroder, "4", "6", false);
}
