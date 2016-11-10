#include "graph/maze/mazealdousbroder.h"
#include "bootstrap/convenient_maze_textonly.h"

int main(int argc, char **argv) {
    //Dimensions default    4
    //Edge length default   6
    return convenient_maze_textonly::init(argc, argv, new MazeAldousBroder, "4", "6");
}
