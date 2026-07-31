#ifndef HELPER_H
#define HELPER_H
#include <vector>
bool checkinRow(int board[25][25], int row, int num);
bool checkinCol(int board[25][25], int col, int num);
bool checkinBox(int board[25][25], int row, int col, int num);
void printBoard(int board[25][25]);
bool isSingleInput(int board[25][25], std::vector<int> possibleInputs);
bool noExistsInRow(int board[25][25], int row, int candidate);
bool noExistsInCol(int board[25][25], int col, int candidate);
bool noExistsInBox(int board[25][25], int row, int col, int candidate);
bool if_It_Is_Only_In_Row(int board[25][25], int row);
bool if_It_Is_Only_In_Col(int board[25][25], int col);
bool if_It_Is_Only_In_Box(int board[25][25], int row, int col);
bool checkIfBoardIsFilled(int board[25][25]);
bool backtrack(int board[25][25]);
#endif