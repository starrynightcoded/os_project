#include <iostream>
#include <vector>
using namespace std;
int inputs[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int board[9][9] = {{1, 0, 0, 0, 0, 7, 0, 9, 0}, {0, 3, 0, 0, 2, 0, 0, 0, 8},
                   {0, 0, 9, 6, 0, 0, 5, 0, 0}, {0, 0, 5, 3, 0, 0, 9, 0, 0},
                   {0, 1, 0, 0, 8, 0, 0, 0, 2}, {6, 0, 0, 0, 0, 4, 0, 0, 0},
                   {3, 0, 0, 0, 0, 0, 0, 1, 0}, {0, 4, 0, 0, 0, 0, 0, 0, 7},
                   {0, 0, 7, 0, 0, 0, 3, 0, 0}};
bool checkinRow(int board[9][9], int row,
                int num) { // if exists then return true
  for (int col = 0; col < 9; col++) {
    if (board[row][col] == num) {
      return true;
    }
  }
  return false;
}
bool checkinCol(int board[9][9], int col, int num) {
  for (int row = 0; row < 9; row++) {
    if (board[row][col] == num) {
      return true;
    }
  }
  return false;
}
bool checkinBox(int board[9][9], int row, int col, int num) {
  // 3 6 9
  int i, j, limitRow, limitCol, initialRow, initialCol;
  if (row >= 0 && row < 3 && col >= 0 && col < 3) {
    initialRow = 0;
    initialCol = 0;

  } else if (row >= 0 && row < 3 && col >= 3 && col < 6) {
    initialRow = 0;
    initialCol = 3;

  } else if (row >= 0 && row < 3 && col >= 6 && col < 9) {
    initialRow = 0;
    initialCol = 6;
  } else if (col >= 0 && col < 3 && row >= 0 && row < 3) {
    initialCol = 0;
    initialRow = 0;

  } else if (col >= 0 && col < 3 && row >= 3 && row < 6) {
    initialCol = 0;
    initialRow = 3;

  } else if (col >= 0 && col < 3 && row >= 6 && row < 9) {
    initialCol = 0;
    initialRow = 6;
  } else if (row >= 3 && row < 6 && col >= 3 && col < 6) {
    initialRow = 3;
    initialCol = 3;
  } else if (row >= 3 && row < 6 && col >= 6 && col < 9) {
    initialRow = 3;
    initialCol = 6;
  } else if (row >= 6 && row < 9 && col >= 3 && col < 6) {
    initialRow = 6;
    initialCol = 3;
  } else if (row >= 6 && row < 9 && col >= 6 && col < 9) {
    initialRow = 6;
    initialCol = 6;
  }

  limitRow = initialRow + 3;
  limitCol = initialCol + 3;
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
void printBoard(int board[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
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
int num;

bool noExistsInRow(int board[9][9], int row, int candidate) {
  for (int i = 0; i < 9; i++) {
    if (board[row][i] == candidate) {
      return true; // candidate does not exist
    }
  }
  return false; //  candidate already exists
}

bool if_It_Is_Only_In_Row(int board[9][9], int row) {
  int zeroCount = 0;
  int zeroCol = -1;

  for (int i = 0; i < 9; i++) {
    if (board[row][i] == 0) {
      zeroCount++;
      zeroCol = i;
    }
  }

  if (zeroCount == 1) {
    for (int i = 0; i < 9; i++) {
      if (!noExistsInRow(board, row, inputs[i]) &&
          !checkinCol(board, zeroCol, inputs[i]) &&
          !checkinBox(board, row, zeroCol, inputs[i])) {
        board[row][zeroCol] = inputs[i];
        return true;
      }
    }
  }

  return false;
}
bool noExistsInCol(int board[9][9], int col, int candidate) {
  for (int i = 0; i < 9; i++) {
    if (board[i][col] == candidate) {
      return true;
    }
  }
  return false;
}
bool if_It_Is_Only_In_Col(int board[9][9], int col) {
  int zeroCount = 0;
  int zeroRow = -1;
  for (int i = 0; i < 9; i++) {
    if (zeroCount > 1) {
      return false;
    }
    if (board[i][col] == 0) {
      zeroCount++;
      zeroRow = i;
    }
  }
  if (zeroCount == 1) {
    for (int i = 0; i < 9; i++) {
      if (!noExistsInCol(board, col, inputs[i]) &&
          !checkinCol(board, col, inputs[i]) &&
          !checkinBox(board, zeroRow, col, inputs[i]) &&
          !checkinRow(board, zeroRow, inputs[i])) {
        board[zeroRow][col] = inputs[i];
        return true;
      }
    }
  }
  return false;
}
bool noExistsInBox(int board[9][9], int row, int col, int candidate) {
  int startRow = (row / 3) * 3;
  int startCol = (col / 3) * 3;
  for (int i = startRow; i < startRow + 3; i++) {
    for (int j = startCol; j < startCol + 3; j++) {
      if (board[i][j] == candidate) {
        return true;
      }
    }
  }
  return false;
}
bool if_It_Is_Only_In_Box(int board[9][9], int row, int col) {
  int zeroCount = 0;
  int zeroRow = -1;
  int zeroCol = -1;
  int startRow = (row / 3) * 3;
  int startCol = (col / 3) * 3; // thanks to a simple google search
  for (int i = startRow; i < startRow + 3; i++) {
    for (int j = startCol; j < startCol + 3; j++) {
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
    for (int k = 0; k < 9; k++) {
      if (!noExistsInBox(board, row, col, inputs[k]) &&
          !checkinCol(board, zeroCol, inputs[k]) &&
          !checkinBox(board, zeroRow, zeroCol, inputs[k]) &&
          !checkinRow(board, zeroRow, inputs[k])) {
        board[zeroRow][zeroCol] = inputs[k];
        return true;
      }
    }
  }
  return false;
}

bool checkIfBoardIsFilled(int board[9][9]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}
bool backtrack(int board[9][9]) {
  if (checkIfBoardIsFilled(board)) {
    return true;
  }
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == 0) {
        // find possibilities
        vector<int> possibleInputs;
        for (int k = 0; k < 9; k++) {
          if (!checkinRow(board, i, inputs[k]) &&
              !checkinCol(board, j, inputs[k]) &&
              !checkinBox(board, i, j, inputs[k])) {
            possibleInputs.push_back(inputs[k]);
          }
        }
        for (int l = 0; l < possibleInputs.size(); l++) {
          // try one possibility
          board[i][j] = possibleInputs[l];
          if (backtrack(board)) {
            return true;
          } else {
            board[i][j] = 0;
          }
        }
        return false;
      }
    }
  }
  return false;
}
int main() {

  cout << "Printing board as is: " << endl;
  printBoard(board);
  bool changeMade = true;
  while (changeMade) {
    changeMade = false;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] == 0) {
          // try a valid possibility
          vector<int> possibleInputs;
          for (int k = 0; k < 9; k++) {
            if (!checkinRow(board, i, inputs[k]) &&
                !checkinCol(board, j, inputs[k]) &&
                !checkinBox(board, i, j, inputs[k])) {
              possibleInputs.push_back(inputs[k]);
            }
          }
          // cout << " possible inputs size is: " << possibleInputs.size();
          if (isSingleInput(board, possibleInputs)) {
            board[i][j] = possibleInputs[0];
            changeMade = true;
          }
          if (if_It_Is_Only_In_Col(board, j)) {
            changeMade = true;
          }
          if (if_It_Is_Only_In_Row(board, i)) {
            changeMade = true;
          }
          if (if_It_Is_Only_In_Box(board, i, j)) {
            changeMade = true;
          }
        }
      }
    }
  }
  cout << endl;
  cout << endl;
  if (checkIfBoardIsFilled(board)) {
    cout << "Board is filled successfully!" << endl;
    printBoard(board);
  } else {
    // backtrack
    cout << "Board is filled successfully after backtracking!" << endl;
    backtrack(board);
    printBoard(board);
  }

  return 0;
}