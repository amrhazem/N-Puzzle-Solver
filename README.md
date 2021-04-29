# N-Puzzle-Solver
## Problem Definition
The N-Puzzle is known in finite versions such as the 8-puzzle (a 3x3 board) and the 15-puzzle (a 4x4 board), and with various names like "sliding block", "tile puzzle", etc. The N-Puzzle is a board game for a single player. It consists of (N) numbered squared tiles in random order, and one blank space ("a missing tile"). 

The objective of the puzzle is to rearrange the tiles in order by making sliding moves that use the empty space, using the fewest moves. Moves of the puzzle are made by sliding an adjacent tile into the empty space. Only tiles that are horizontally or vertically adjacent to the blank space (not diagonally adjacent) may be moved.

![Image of 3x3Board](https://github.com/amrhazem/N-Puzzle-Solver/blob/main/3x3%20Board%20Example.png)

## Applying A* Search Algorithm
The N-puzzle (N = 8, 15...) is a classical problem for modelling algorithms involving heuristics. Commonly used heuristics for this problem include counting the number of misplaced tiles (Hamming Distance) OR finding the sum of the Manhattan distances between each block and its position in the goal configuration. Note that both are admissible, i.e. they never overestimate the number of moves left, which ensures optimality for certain search algorithms such as A*. A* is one of the informed search algorithms that can be used in such problems to get the optimal solution.

## User-Manual(Guide)
1. Read in a file containing an N puzzle with (N) numbered tiles and one blank space – representing an initial state. (Put the path manually in code)
2. The program will detect whether the board is solvable or not at first.
3. If solvable: Step-by-step solution will appear to get the shortest path to get the final solution.
4. You can also choose whether to solve it using Hamming Priority Function or Manhattan Priority Function.

**NOTE: The project must run under 32 bits(x86).**

## Bonus
1. Simulating user friendly GUI which allows you to rewind the search one step (movement) at a time over a 3x3 Puzzles only.
2. Applying BFS algorithm in order to show the difference between it and A* to solve the unordered board in terms of the number of movements done by each and time.
