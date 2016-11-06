#include "graph/maze/mazewilsons.h"
#include "bootstrap/rendered.h"

int main(int argc, char **argv) {
    //Dimensions default    3
    //Edge length default   10
    return run(argc, argv, new MazeWilsons, "3", "10");
}
