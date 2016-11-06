#include "graph/maze/mazebinary.h"
#include "bootstrap/rendered.h"

int main(int argc, char **argv) {
    //Dimensions default    2
    //Edge length default   18
    return run(argc, argv, new MazeBinary, "2", "18");
}
