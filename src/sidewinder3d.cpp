#include "graph/maze/mazesidewinder.h"
#include "bootstrap/convenient_maze_opengl.h"

int main(int argc, char **argv) {
    //Dimensions default    3
    //Edge length default   8
    //Render opengl
    return convenient_maze_opengl::init(argc, argv, new MazeSidewinder, "3", "8", 0);
}
