#include "graph/maze/mazewilsons.h"
#include "bootstrap/rendered.h"

int main(int argc, char **argv) {
    //Dimensions default    2
    //Edge length default   18
    return run(argc, argv, new MazeWilsons, "2", "18");
}
