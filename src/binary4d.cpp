#include "graph/maze/mazebinary.h"
#include "bootstrap/textonly.h"

int main(int argc, char **argv) {
    return run(argc, argv, new MazeBinary, "4", "6");
}