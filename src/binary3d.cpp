#include "graph/maze/mazebinary.h"
#include "bootstrap/rendered.h"

int main(int argc, char **argv) {
    //Dimensions default    3
    //Edge length default   10
    return run(argc, argv, new MazeBinary, "3", "10");
}
