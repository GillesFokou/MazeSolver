/**
 * @file MazeSolver.cpp
 * @brief Implementation of the MazeSolver class methods and program entry point.
 */

#include "MazeSolver.h"
#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#endif

 /** @name ANSI Color Constants
  * Group of constants used to colorize the console output.
  */
  ///@{
const std::string RED = "\033[31m"; ///< Color for the start point (2)
const std::string GREEN = "\033[32m"; ///< Color for the solution path (4)
const std::string BLUE = "\033[34m"; ///< Color for the exit point (3)
const std::string RESET = "\033[0m";  ///< Reset terminal to default color
///@}

/**
 * @brief Default constructor.
 * Initializes the grid dimensions and starting point to default values.
 */
MazeSolver::MazeSolver() : rows(0), cols(0), startX(-1), startY(-1) {}

/**
 * @brief Loads the maze structure from a text file.
 * @param filename Path to the .txt file containing the maze.
 * @return true if loading and start point detection are successful.
 */
bool MazeSolver::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    if (!(file >> rows >> cols)) return false;
    grid.assign(rows, std::vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        std::string line;
        file >> line;
        for (int j = 0; j < (int)line.length() && j < cols; ++j) {
            grid[i][j] = line[j] - '0';
            if (grid[i][j] == 2) {
                startX = i; startY = j;
            }
        }
    }
    file.close();
    return (startX != -1);
}

/**
 * @brief Checks if a move to the specified cell is valid.
 * @param r Row index.
 * @param c Column index.
 * @return true if the cell is within bounds and is a path (0) or exit (3).
 */
bool MazeSolver::isValid(int r, int c) const {
    return (r >= 0 && r < rows && c >= 0 && c < cols &&
        (grid[r][c] == 0 || grid[r][c] == 3));
}

/**
 * @brief Core recursive function (DFS) to navigate the maze.
 * @param r Current row.
 * @param c Current column.
 * @return true if the exit point is reached.
 */
bool MazeSolver::explore(int r, int c) {
    if (grid[r][c] == 3) return true;

    bool isEntrance = (grid[r][c] == 2);
    if (!isEntrance) grid[r][c] = 4; 

    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (isValid(nr, nc)) {
            if (explore(nr, nc)) return true;
        }
    }

    if (!isEntrance) grid[r][c] = 0;
    return false;
}

/**
 * @brief Initiates the maze solving process.
 * @return true if a solution exists from the identified starting point.
 */
bool MazeSolver::solve() {
    return (startX != -1) ? explore(startX, startY) : false;
}

/**
 * @brief Prints the maze to the console with ANSI colors.
 * Highlights start, exit, and the discovered solution path.
 */
void MazeSolver::displaySolution() const {
    std::cout << rows << "\n" << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int cell = grid[i][j];
            if (cell == 2) std::cout << RED << cell << RESET;
            else if (cell == 3) std::cout << BLUE << cell << RESET;
            else if (cell == 4) std::cout << GREEN << cell << RESET;
            else std::cout << cell;
        }
        std::cout << "\n";
    }
}

/**
 * @brief Main function.
 * Handles command-line arguments, enables Windows ANSI support,
 * and executes the MazeSolver workflow.
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <maze.txt>" << std::endl;
        return 1;
    }

#ifdef _WIN32
    
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif

    MazeSolver solver;
    if (solver.loadFromFile(argv[1])) {
        if (solver.solve()) {
            solver.displaySolution();
        }
        else {
            std::cout << "No path found." << std::endl;
        }
    }
    else {
        std::cerr << "Error: File not found or invalid format." << std::endl;
        return 1;
    }
    return 0;
}