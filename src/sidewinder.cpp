#include "graph/maze/mazesidewinder.h"
#include "bootstrap/textonly.h"

int main(int argc, char **argv) {
    return run(argc, argv, new MazeSidewinder, "4", "6");
}