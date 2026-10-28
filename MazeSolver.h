/**
 * @file MazeSolver.h
 * @brief Declaration of the MazeSolver class for grid-based pathfinding.
 */

#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include <vector>
#include <string>

 /**
  * @class MazeSolver
  * @brief Implements a Backtracking algorithm to solve a maze.
  * * This class handles loading a grid from a file, finding a path
  * from a start point (2) to an exit (3), and displaying the result.
  */
class MazeSolver {
public:
    /**
     * @brief Default constructor.
     */
    MazeSolver();

    /**
     * @brief Loads the maze structure from a text file.
     * @param filename Path to the input .txt file.
     * @return true if loading and entrance detection were successful.
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Executes the pathfinding algorithm.
     * @return true if a path to the exit (3) was found.
     */
    bool solve();

    /**
     * @brief Outputs the solved maze to the console with ANSI colors.
     */
    void displaySolution() const;

private:
    int rows, cols;                             ///< Maze dimensions
    int startX, startY;                         ///< Starting coordinates (value 2)
    std::vector<std::vector<int>> grid;         ///< 2D grid representation

    /**
     * @brief Recursive Depth-First Search (DFS) function to explore the maze.
     * @param r Current row index.
     * @param c Current column index.
     * @return true if the current path leads to the exit.
     */
    bool explore(int r, int c);

    /**
     * @brief Validates if a move to (r, c) is allowed.
     * @param r Row index.
     * @param c Column index.
     * @return true if within bounds and not a wall.
     */
    bool isValid(int r, int c) const;
};

#endif