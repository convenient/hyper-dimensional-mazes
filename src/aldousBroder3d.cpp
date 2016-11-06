#include "graph/maze/mazealdousbroder.h"
#include "bootstrap/rendered.h"

int main(int argc, char **argv) {
    return run(argc, argv, new MazeAldousBroder, "3", "10");
}
