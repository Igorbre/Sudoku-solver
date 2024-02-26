#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 9;

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place the digit in the given position
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check the row and column
    for (int x = 0; x < SIZE; ++x) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to find an empty cell in the Sudoku grid
bool findEmptyCell(const vector<vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < SIZE; ++row) {
        for (col = 0; col < SIZE; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Function to solve Sudoku using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;

    // Find an empty cell
    if (!findEmptyCell(grid, row, col)) {
        // If no empty cell is found, the Sudoku is solved
        return true;
    }

    // Try placing a digit in the cell
    for (int num = 1; num <= SIZE; ++num) {
        if (isSafe(grid, row, col, num)) {
            // Place the digit
            grid[row][col] = num;

            // Recur to solve the rest of the Sudoku
            if (solveSudoku(grid)) {
                return true;
            }

            // If placing the digit leads to contradiction, backtrack
            grid[row][col] = 0;
        }
    }

    // If no digit can be placed, return false
    return false;
}

int main() {
    vector<vector<int>> sudokuGrid;

    cout << "Enter the Sudoku puzzle (use 0 for empty cells):" << endl;
    for (int i = 0; i < SIZE; ++i) {
        vector<int> row;
        for (int j = 0; j < SIZE; ++j) {
            int cellValue;
            cin >> cellValue;
            row.push_back(cellValue);
        }
        sudokuGrid.push_back(row);
    }

    cout << "\nSudoku Puzzle:" << endl;
    printGrid(sudokuGrid);

    if (solveSudoku(sudokuGrid)) {
        cout << "\nSudoku Solution:" << endl;
        printGrid(sudokuGrid);
    }
    else {
        cout << "\nNo solution exists." << endl;
    }

    return 0;
}
