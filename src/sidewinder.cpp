#include "graph/maze/mazesidewinder.h"
#include "bootstrap/textonly.h"

int main(int argc, char **argv) {
    //Dimensions default    4
    //Edge length default   6
    return run(argc, argv, new MazeSidewinder, "4", "6");
}