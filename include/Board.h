#ifndef BOARD_H
#define BOARD_H

// Simple 9x9 Sudoku board.
// (25x25 version will be a separate Board25 class made by your teammate)
class Board {
public:
    static const int SIZE = 9;
    int grid[SIZE][SIZE];

    Board();
    void loadDefaultPuzzle();

    bool checkInRow(int row, int num) const;
    bool checkInCol(int col, int num) const;
    bool checkInBox(int row, int col, int num) const;

    bool isFilled() const;
    void print() const;
};

#endif