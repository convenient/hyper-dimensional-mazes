#include "graph/maze/mazewilsons.h"
#include "bootstrap/textonly.h"

int main(int argc, char **argv) {
    return run(argc, argv, new MazeWilsons, "4", "6");
}
