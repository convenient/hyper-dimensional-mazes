#include "graph/maze/mazealdousbroder.h"
#include "bootstrap/textonly.h"

int main(int argc, char **argv) {
    //Dimensions default    4
    //Edge length default   6
    return run(argc, argv, new MazeAldousBroder, "4", "6");
}
