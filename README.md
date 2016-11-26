# mazes-for-programmers
A C++ and OpenGL implementation of different varieties of N-Dimensional mazes. All based very loosely on the topics covered in the [Mazes for Programmers](https://pragprog.com/book/jbmaze/mazes-for-programmers) book.

What this repo attempts to achieve is the following:

1. To break down typically described maze generation algorithms and to refactor them so that they are agnostic of any sense of Up/Down/Left/Rights. Any "dimensionality" in the algorithm needs removed.
2. Generate a 2D visualisation of the maze using the refactored algorithm, to validate that it works.
3. Using the same algorithm, generate a 3D visualisation to see what the potential maze and solution looks like with a new dimension.
4. Generate a 4D version of the maze. There are no visualisations for these higher dimensional mazes because I don't have access to that much LSD. This will simply output a text description of the mazes solution.

I'll start with the binary maze as an in depth example as it's the simplest. I'll go a bit more in depth to the process here to help explain what's going on.

# Binary Maze

A binary maze can simply be described as "For every node in the maze randomly carve a passage up or right", and it is easily recognised by the long straight passes you get on two sides of the maze. 

Programatically this got refactored to

    For every node in the maze
        For every axis in the maze
            If there is a neighbouring node +1 on that axis
                Add to list of PotentialNodes
        Select a node randomly from the PotentialNodes
        Carve into randomly selected node

Removing all sense of direction from the algorithm makes it ugly and complicated, but it means the same algorithm will produce the same results in 2D but will also scale to ND dimensions without problem.

- [Click here to see the binary algorithm](src/mazebinary.h)
- [Click here to see the generation of a 2D binary maze](src/binary2dgrid.cpp)
- [Click here to see the generation of a 3D binary maze](src/binary3dgrid.cpp)
- [Click here to see the generation of a 4D binary maze](src/binary4d.cpp)

By comparing the last 3 files the only real difference in the generation of a maze with more dimensions is that you must declare the extra axis when creating the "Point" for the node. 

## Binary Maze 2D

## Binary Maze 3D

## Binary Maze 4D

#Dependencies

- OpenGL

    ```
    sudo apt-get install freeglut3
    sudo apt-get install freeglut3-dev
    ```
    
- [cxxopts](https://github.com/jarro2783/cxxopts)
- [NestedLoops.h](src/lib/NestedLoop/README.md)
