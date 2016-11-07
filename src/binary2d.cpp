#include "graph/maze/mazebinary.h"
#include "bootstrap/convenient_maze.h"

int main(int argc, char **argv) {
    //Dimensions default    2
    //Edge length default   18
    //Render opengl
    return convenient_maze::init(argc, argv, new MazeBinary, "2", "18", true);
}
