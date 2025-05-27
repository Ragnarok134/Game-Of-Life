Project Title: Game Of Life

Description:
Game Of Life reffers to an algorithm applied on an initial set of "cells" stored in the form of a matrix that simulates their evolution through generations based on a set of rules based on each cell's number of alive 
neighbours. Despite the simplicity of these rules, the predictability of the next generation becomes lower and lower as the "game" progresses, because the complexity of the cells' layout grows exponentially as the 
rules apply to each and every single cell, these being able to survive, die and even come back to life. The project is devided into 4 tasks, each adding another layer of complexity and optimization to the game. 

Dependencies:
- stdio.h
- stdlib.h
- string.h
- course checker

How to use:
To function, the program needs the number of the task you want it to perform, the size of the matrix in which the cells are stored, the number of generations you want it to simulate and then the initial matrix of 
cells. The alive cells are represented with 'X' and the dead ones with '+'. This program needs to be run through the command line and these informations need to be given through a .in document and the output is
given through an .out file. 

Tasks descriptions:
- Task 1:
This task will display all the simulated up to the number read from the input file. To do this, the initial matrix was updated for each generation by applying the set of rules to each cell.
- Task 2:
This task will carry out the same job as the previous one, but this time with an optimization: For each generation, the coordinates of the cells that that change from one generation to another and store these pairs
in lists that are stored in a stack.
- Task 3:
This task adds a new option for each generation: applying a new set of rules. This time, the generations will be stored in nodes. Each node will contain the coordinates of the cells that change from one generation
to another, same as in the previous task, but this time without a stack. Each node has 2 children, the one on the left containing the evolution after applying the new set of rules and the one on the right contains
the evolution after applying the standard set of rules.
- Task 4:
This task uses the tree created using the same principle as the last task, but this time it will also represent each generation of cells through a graph, each alive cell representing a node. With this new set of
information, it needs to determine the longest hamiltonian chain from a conex component from each generation and display its length and the coordinates of the component nodes.

Checker:
The course checker is installed from: https://gitlab.cs.pub.ro/paaa/checker/-/releases
