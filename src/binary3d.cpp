#include "graph/maze/mazebinary.h"
#include "bootstrap/rendered.h"

int main(int argc, char **argv) {
    return run(argc, argv, new MazeBinary, "3", "10");
}
