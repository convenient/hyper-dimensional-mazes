#include "graph/maze/mazebinary.h"
#include "bootstrap/convenient_maze_opengl.h"

int main(int argc, char **argv) {
    //Dimensions default    2
    //Edge length default   18
    //Render opengl
    return convenient_maze_opengl::init(argc, argv, new MazeBinary, "2", "18");
}
