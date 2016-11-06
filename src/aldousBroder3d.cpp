#include "graph/maze/mazealdousbroder.h"
#include "bootstrap/rendered.h"

int main(int argc, char **argv) {
    //Dimensions default    3
    //Edge length default   10
    return run(argc, argv, new MazeAldousBroder, "3", "10");
}
