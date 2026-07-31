#include "SequentialSolver.h"
#include <vector>
using namespace std;

static int inputs[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

// If the easy moves don't solve the board,
// this recursive backtracking method tries different possibilities.
static bool backtrack(Board &board) {
    if (board.isFilled()) return true;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board.grid[i][j] == 0) {
                for (int k = 0; k < 9; k++) {
                    int num = inputs[k];
                    if (!board.checkInRow(i, num) &&
                        !board.checkInCol(j, num) &&
                        !board.checkInBox(i, j, num)) {
                        board.grid[i][j] = num;
                        if (backtrack(board)) return true;
                        board.grid[i][j] = 0; // undo, try next candidate (possible value that can be placed in the cell)
                    }
                }
                return false; // no candidate (possible value that can be placed in the cell) worked for this cell
            }
        }
    }
    return false;
}

// One pass over the board: any empty cell with exactly one legal
// candidate gets filled in immediately.
static void fillSingleCandidates(Board &board, bool &changeMade) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board.grid[i][j] == 0) {
                vector<int> possible;
                for (int k = 0; k < 9; k++) {
                    int num = inputs[k];
                    if (!board.checkInRow(i, num) &&
                        !board.checkInCol(j, num) &&
                        !board.checkInBox(i, j, num)) {
                        possible.push_back(num);
                    }
                }
                if (possible.size() == 1) {
                    board.grid[i][j] = possible[0];
                    changeMade = true;
                }
            }
        }
    }
}

bool solveSequential(Board &board) {
    bool changeMade = true;
    while (changeMade) {
        changeMade = false;
        fillSingleCandidates(board, changeMade);
    }

    if (board.isFilled()) return true;
    return backtrack(board);
}