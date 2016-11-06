#include "graph/maze/mazewilsons.h"
#include "bootstrap/rendered.h"

int main(int argc, char **argv) {
    return run(argc, argv, new MazeWilsons, "3", "10");
}
