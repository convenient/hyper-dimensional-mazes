#include "graph/maze/mazealdousbroder.h"
#include "bootstrap/textonly.h"

int main(int argc, char **argv) {
    return run(argc, argv, new MazeAldousBroder, "4", "6");
}
