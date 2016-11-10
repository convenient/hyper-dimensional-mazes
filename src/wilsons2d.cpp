#include "graph/maze/mazewilsons.h"
#include "bootstrap/convenient_maze_opengl.h"

int main(int argc, char **argv) {
    //Dimensions default    2
    //Edge length default   18
    //Render opengl
    return convenient_maze::init(argc, argv, new MazeWilsons, "2", "18");
}
