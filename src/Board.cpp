#include "Board.h"
#include <iostream>
using namespace std;

Board::Board() {
    loadDefaultPuzzle();
}

void Board::loadDefaultPuzzle() {
    int starter[9][9] = {
        {1, 0, 0, 0, 0, 7, 0, 9, 0},
        {0, 3, 0, 0, 2, 0, 0, 0, 8},
        {0, 0, 9, 6, 0, 0, 5, 0, 0},
        {0, 0, 5, 3, 0, 0, 9, 0, 0},
        {0, 1, 0, 0, 8, 0, 0, 0, 2},
        {6, 0, 0, 0, 0, 4, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 4, 0, 0, 0, 0, 0, 0, 7},
        {0, 0, 7, 0, 0, 0, 3, 0, 0}
    };

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            grid[i][j] = starter[i][j];
}

bool Board::checkInRow(int row, int num) const {
    for (int col = 0; col < SIZE; col++)
        if (grid[row][col] == num) return true;
    return false;
}

bool Board::checkInCol(int col, int num) const {
    for (int row = 0; row < SIZE; row++)
        if (grid[row][col] == num) return true;
    return false;
}

bool Board::checkInBox(int row, int col, int num) const {
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = startRow; i < startRow + 3; i++)
        for (int j = startCol; j < startCol + 3; j++)
            if (grid[i][j] == num) return true;
    return false;
}

bool Board::isFilled() const {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (grid[i][j] == 0) return false;
    return true;
}

void Board::print() const {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            cout << grid[i][j] << " , ";
        cout << endl;
    }
}