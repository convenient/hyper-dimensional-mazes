#include "graph/maze/mazerecursivebacktracker.h"
#include "bootstrap/convenient_maze_textonly.h"

int main(int argc, char **argv) {
    //Dimensions default    2
    //Edge length default   6
    return convenient_maze_textonly::init(argc, argv, new MazeRecursiveBacktracker, "4", "6");
}
