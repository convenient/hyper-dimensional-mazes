#include "graph/maze/mazesidewinder.h"
#include "bootstrap/rendered.h"

int main(int argc, char **argv) {
    return run(argc, argv, new MazeSidewinder, "3", "10");
}
