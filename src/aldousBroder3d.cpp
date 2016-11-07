#include "graph/maze/mazealdousbroder.h"
#include "bootstrap/convenient_maze.h"

int main(int argc, char **argv) {
    //Dimensions default    3
    //Edge length default   10
    //Render opengl
    return convenient_maze::init(argc, argv, new MazeAldousBroder, "3", "10", true);
}
