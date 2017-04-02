# N-dimensional orthogonal maze generation algorithms

An experimental implementation of some common Maze generation algorithms, modified to support N dimensions. All topics loosely inspired by the [Mazes for Programmers](https://pragprog.com/book/jbmaze/mazes-for-programmers) book.

1. [Defining the Mazes](#defining-the-mazes)
1. [Rendering the Mazes](#rendering-the-mazes)
    1. [Rendering a 2D Maze](#rendering-a-2d-maze)
    1. [Rendering a 3D Maze](#rendering-a-3d-maze)
    1. [Rendering Higher Dimensions](#rendering-higher-dimensions)
1. [Binary Algorithm](#binary-algorithm)
    1. [Binary 2D](#binary-2d)
    1. [Binary 3D](#binary-3d)
    1. [Binary ND](#binary-nd)
1. [Sidewinder Algorithm](#sidewinder-algorithm)
    1. [Sidewinder 2D](#sidewinder-2d)
    1. [Sidewinder 3D](#sidewinder-3d)
    1. [Sidewinder ND](#sidewinder-nd)
1. [Aldous-Broder Algorithm](#aldous-broder-algorithm)
    1. [Aldous-Broder 2D](#aldous-broder-2d)
    1. [Aldous-Broder 3D](#aldous-broder-3d)
    1. [Aldous-Broder ND](#aldous-broder-nd)
1. [Recursive Backtracker Algorithm](#recursive-backtracker-algorithm)
    1. [Recursive Backtracker 2D](#recursive-backtracker-2d)
    1. [Recursive Backtracker 3D](#recursive-backtracker-3d)
    1. [Recursive Backtracker ND](#recursive-backtracker-nd)
1. [Developer Notes](#developer-notes)
   1. [Dependencies](#dependencies)

These modifications are not all very performant, particularly the `Node` and `Point` classes which are the foundation of the dimension agnostic mazes. They sure were interesting though.

Sorry for the GIFs, this didn't deserve its own webpage.

## Defining the Mazes

Generation algorithms don't actually have any concept of the "start" or "end" of a maze and they simply carve out connections between different nodes. This isn't ideal as we can't really appreciate any weaving or texture within the maze without inspecting it in some way.

The following approach of forcing a "start" and "end" node into a maze helps highlight defining characteristics of the different algorithms as each algorithm has its own footprint.

The approach taken for this project is

1. Generate a maze using any algorithm
2. Iterate through every node in the graph
    2. If this node has only one other node connected it is a "dead end".
    3. If this node is on the "edge" of the maze.
    3. Add to list of "dead end" nodes.
3. Compute the "all pairs all paths" problem between all of these dead ends using a breadth first search in dijkstras algorithm.
4. Find the pairs with the longest distance and mark them as the "start" and "end".

There are some cool performance modifications to the breadth first search described in step 3, if you are interested the entrypoints are `src/graph/solver.h` and `src/graph/dijkstra.h`.

## Rendering the Mazes

### Rendering a 2D Maze

Render as you'd expect, as if you draw them on a piece of paper.

### Rendering a 3D Maze

Like a stacked 2D maze, as you'd expect. It's difficult to see the solution happening "inside" the graph but it is there.

### Rendering Higher Dimensions

This is a purely textual renderer, I started playing around with a renderer that would cycle through dimensions (see commit here TODO) but I didn't understand what I was looking at near the end. If anyone wants to down a gallon of LSD and revisit this feel free.

# Binary Algorithm

> Pick a random unvisited node, carve a path north or east. Pick until all nodes are visited.

See `src/graph/maze/mazebinary.h`.

This was quite a simple one to translate into higher dimensions, simply stack the extra dimensions in the maze and pick a possible dimension form the list.

## Binary 2D


| Visual Graph        | Text Graph           |
| ------------- |:-------------:|
| ![binary2d](readme/binary2d.gif) | Using seed: 1485002677078
                                          Generating a Binary maze of 12 by 12
                                          Ensuring solution
                                          Solution took 0.0256184 seconds and has a distance of 40
                                          (x:-1)(y:-6) to (x:-6)(y:-6)
                                          start at          (x:-1)(y:-6)
                                          positive 1 on y   (x:-1)(y:-5)
                                          positive 1 on x   (x:0)(y:-5)
                                          positive 1 on y   (x:0)(y:-4)
                                          positive 1 on x   (x:1)(y:-4)
                                          positive 1 on y   (x:1)(y:-3)
                                          positive 1 on x   (x:2)(y:-3)
                                          positive 1 on x   (x:3)(y:-3)
                                          positive 1 on y   (x:3)(y:-2)
                                          positive 1 on x   (x:4)(y:-2)
                                          positive 1 on x   (x:5)(y:-2)
                                          positive 1 on y   (x:5)(y:-1)
                                          positive 1 on y   (x:5)(y:0)
                                          positive 1 on y   (x:5)(y:1)
                                          positive 1 on y   (x:5)(y:2)
                                          positive 1 on y   (x:5)(y:3)
                                          positive 1 on y   (x:5)(y:4)
                                          positive 1 on y   (x:5)(y:5)
                                          negative 1 on x   (x:4)(y:5)
                                          negative 1 on x   (x:3)(y:5)
                                          negative 1 on x   (x:2)(y:5)
                                          negative 1 on x   (x:1)(y:5)
                                          negative 1 on y   (x:1)(y:4)
                                          negative 1 on x   (x:0)(y:4)
                                          negative 1 on y   (x:0)(y:3)
                                          negative 1 on y   (x:0)(y:2)
                                          negative 1 on y   (x:0)(y:1)
                                          negative 1 on y   (x:0)(y:0)
                                          negative 1 on y   (x:0)(y:-1)
                                          negative 1 on y   (x:0)(y:-2)
                                          negative 1 on x   (x:-1)(y:-2)
                                          negative 1 on x   (x:-2)(y:-2)
                                          negative 1 on x   (x:-3)(y:-2)
                                          negative 1 on x   (x:-4)(y:-2)
                                          negative 1 on y   (x:-4)(y:-3)
                                          negative 1 on x   (x:-5)(y:-3)
                                          negative 1 on x   (x:-6)(y:-3)
                                          negative 1 on y   (x:-6)(y:-4)
                                          negative 1 on y   (x:-6)(y:-5)
                                          finish at         (x:-6)(y:-6) |

## Binary 3D

![binary3d](readme/binary3d.gif)


## Binary ND

Here's a command line example of

```
```

# Sidewinder Algorithm

## Sidewinder 2D

## Sidewinder 3D

## Sidewinder ND

# Aldous-Broder Algorithm

## Aldous-Broder 2D

## Aldous-Brodger 3D

## Aldous-Broder ND

# Recursive Backtracker Algorithm

## Recursive Backtracker 2D

## Recursive Backtracker 3D

## Recursive Backtracker ND

# Developer Notes

## Dependencies

- OpenGL

    ```
    sudo apt-get install freeglut3
    sudo apt-get install freeglut3-dev
    ```
    
- [cxxopts](https://github.com/jarro2783/cxxopts)
- [NestedLoops.h](src/lib/NestedLoop/README.md)
