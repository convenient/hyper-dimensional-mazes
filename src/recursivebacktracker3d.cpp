#include "graph/maze/mazerecursivebacktracker.h"
#include "bootstrap/convenient_maze_opengl.h"

int main(int argc, char **argv) {
    //Dimensions default    2
    //Edge length default   8
    //Render opengl
    return convenient_maze_opengl::init(argc, argv, new MazeRecursiveBacktracker, "3", "8");
}
