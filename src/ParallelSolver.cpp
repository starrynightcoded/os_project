#include "ParallelSolver.h"
#include "SequentialSolver.h"
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
using namespace std;

static int inputs[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

// Guards every read/write of board.grid so two threads never
// check/update the board at the same time (the "concurrency control").
static mutex boardMutex;

// Each thread is given its own fixed range of rows (start and end).
// It fills in any cell in those rows that has exactly one legal candidate.
static void solveRows(Board &board, int startRow, int endRow, char &changed) {
    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < 9; j++) {

            lock_guard<mutex> lock(boardMutex); // enter critical section

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
                    changed = 1;
                }
            }
            // lock released automatically here (end of scope)
        }
    }
}

bool solveParallel(Board &board, int numThreads) {
    if (numThreads < 1) numThreads = 1;
    if (numThreads > 9) numThreads = 9; // no point having more threads than rows

    bool changeMade = true;

    while (changeMade) {
        changeMade = false;

        vector<thread> threads;
        vector<char> localChange(numThreads, 0);

        int rowsPerThread = 9 / numThreads;
        if (rowsPerThread == 0) rowsPerThread = 1;

        int row = 0;
        for (int t = 0; t < numThreads && row < 9; t++) {
            int startRow = row;
            int endRow = (t == numThreads - 1) ? 9 : min(9, startRow + rowsPerThread);

            threads.push_back(thread(solveRows, ref(board), startRow, endRow, ref(localChange[t])));
            row = endRow;
        }

        for (auto &th : threads) th.join();

        for (char c : localChange)
            if (c) changeMade = true;
    }

    if (board.isFilled()) return true;

    // Backtracking is left sequential on purpose: branching search across
    // threads needs a lot more synchronization than this project needs.
    return solveSequential(board);
}