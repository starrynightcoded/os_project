#include "helper_func.h"
#include <iostream>
#include <vector>

using namespace std;
int num;
int inputs[25] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13,
                  14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
bool checkinRow(int board[25][25], int row,
                int num) { // if exists then return true
  for (int col = 0; col < 25; col++) {
    if (board[row][col] == num) {
      return true;
    }
  }
  return false;
}

bool checkinCol(int board[25][25], int col, int num) {
  for (int row = 0; row < 25; row++) {
    if (board[row][col] == num) {
      return true;
    }
  }
  return false;
}

bool checkinBox(int board[25][25], int row, int col, int num) {

  int initialRow = (row / 5) * 5;
  int initialCol = (col / 5) * 5;
  int limitRow = initialRow + 5;
  int limitCol = initialCol + 5;
  //   cout << "LimitRow is: " << limitRow << endl;
  //   cout << "LimitCol is: " << limitCol << endl;
  for (int i = initialRow; i < limitRow; i++) {
    for (int j = initialCol; j < limitCol; j++) {
      //   cout << "i: " << i << " j: " << j << " element: " << board[i][j]
      //        << " Outside" << endl;
      if (board[i][j] == num) {
        // cout << "i: " << i << " j: " << j << " element: " << board[i][j]
        //      << " inside" << endl;
        return true;
      }
    }
  }
  return false;
}
void printBoard(int board[25][25]) {
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      cout << board[i][j] << " , ";
    }
    cout << endl;
  }
}

bool isSingleInput(int board[9][9], vector<int> possibleInputs) {
  if (possibleInputs.size() == 1) {
    return true;
  }
  return false;
}

bool noExistsInRow(int board[25][25], int row, int candidate) {
  for (int i = 0; i < 25; i++) {
    if (board[row][i] == candidate) {
      return true; // candidate already exists
    }
  }
  return false; // candidate does not exist
}

bool noExistsInCol(int board[25][25], int col, int candidate) {
  for (int i = 0; i < 25; i++) {
    if (board[i][col] == candidate) {
      return true;
    }
  }
  return false;
}

bool noExistsInBox(int board[25][25], int row, int col, int candidate) {
  int startRow = (row / 5) * 5;
  int startCol = (col / 5) * 5;
  for (int i = startRow; i < startRow + 5; i++) {
    for (int j = startCol; j < startCol + 5; j++) {
      if (board[i][j] == candidate) {
        return true;
      }
    }
  }
  return false;
}

bool if_It_Is_Only_In_Row(int board[25][25], int row) {
  int zeroCount = 0;
  int zeroCol = -1;

  for (int i = 0; i < 25; i++) {
    if (board[row][i] == 0) {
      zeroCount++;
      zeroCol = i;
    }
  }

  if (zeroCount == 1) {
    for (int i = 0; i < 25; i++) {
      if (!noExistsInRow(board, row, inputs[i]) &&
          !noExistsInCol(board, zeroCol, inputs[i]) &&
          !noExistsInBox(board, row, zeroCol, inputs[i])) {
        board[row][zeroCol] = inputs[i];
        return true;
      }
    }
  }
  return false;
}

bool if_It_Is_Only_In_Col(int board[25][25], int col) {
  int zeroCount = 0;
  int zeroRow = -1;
  for (int i = 0; i < 25; i++) {
    if (zeroCount > 1) {
      return false;
    }
    if (board[i][col] == 0) {
      zeroCount++;
      zeroRow = i;
    }
  }
  if (zeroCount == 1) {
    for (int i = 0; i < 25; i++) {
      if (!noExistsInCol(board, col, inputs[i]) &&
          !noExistsInCol(board, col, inputs[i]) &&
          !noExistsInBox(board, zeroRow, col, inputs[i]) &&
          !noExistsInRow(board, zeroRow, inputs[i])) {
        board[zeroRow][col] = inputs[i];
        return true;
      }
    }
  }
  return false;
}

bool if_It_Is_Only_In_Box(int board[25][25], int row, int col) {
  int zeroCount = 0;
  int zeroRow = -1;
  int zeroCol = -1;
  int startRow = (row / 5) * 5;
  int startCol = (col / 5) * 5;
  for (int i = startRow; i < startRow + 5; i++) {
    for (int j = startCol; j < startCol + 5; j++) {
      if (zeroCount > 1) {
        return false;
      }
      if (board[i][j] == 0) {
        zeroCount++;
        zeroRow = i;
        zeroCol = j;
      }
    }
  }
  if (zeroCount == 1) {
    for (int k = 0; k < 25; k++) {
      if (!noExistsInBox(board, row, col, inputs[k]) &&
          !noExistsInCol(board, zeroCol, inputs[k]) &&
          !noExistsInBox(board, zeroRow, zeroCol, inputs[k]) &&
          !noExistsInRow(board, zeroRow, inputs[k])) {
        board[zeroRow][zeroCol] = inputs[k];
        return true;
      }
    }
  }
  return false;
}

bool checkIfBoardIsFilled(int board[25][25]) {
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      if (board[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

bool backtrack(int board[25][25]) {
  if (checkIfBoardIsFilled(board)) {
    return true;
  }
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      if (board[i][j] == 0) {
        // Find possibilities
        std::vector<int> possibleInputs;
        for (int k = 0; k < 25; k++) {
          if (!noExistsInRow(board, i, inputs[k]) &&
              !noExistsInCol(board, j, inputs[k]) &&
              !noExistsInBox(board, i, j, inputs[k])) {
            possibleInputs.push_back(inputs[k]);
          }
        }
        for (size_t l = 0; l < possibleInputs.size(); l++) {

          board[i][j] = possibleInputs[l];
          if (backtrack(board)) {
            return true;
          } else {
            board[i][j] = 0; // Backtrack
          }
        }
        return false;
      }
    }
  }
  return false;
}