#include "parallel_solver.h"
#include "helper_func.h"
#include <iostream>
#include <pthread.h>
#include <vector>

extern int inputs[25];

static int (*globalBoard)[25];
static bool solutionFound = false;

static pthread_mutex_t boardLock = PTHREAD_MUTEX_INITIALIZER;

struct ThreadData {
  int startRow;
  int startCol;
  int startingValue;
};

// sequential solver that stops early if a sibling thread wins
bool backtrackSimple(int board[25][25]) {
  if (solutionFound)
    return false;
  if (checkIfBoardIsFilled(board))
    return true;

  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      if (board[i][j] == 0) {
        for (int k = 0; k < 25; k++) {
          if (solutionFound)
            return false;

          if (!checkinRow(board, i, inputs[k]) &&
              !checkinCol(board, j, inputs[k]) &&
              !checkinBox(board, i, j, inputs[k])) {

            board[i][j] = inputs[k];
            if (backtrackSimple(board))
              return true;
            board[i][j] = 0; // Backtrack
          }
        }
        return false;
      }
    }
  }
  return false;
}

void *workerFunction(void *arg) {

  ThreadData *data = (ThreadData *)arg;

  int localBoard[25][25];

  // Locking the global board just to make a personal copy of it safely
  pthread_mutex_lock(&boardLock);
  for (int r = 0; r < 25; r++) {
    for (int c = 0; c < 25; c++) {
      localBoard[r][c] = globalBoard[r][c];
    }
  }
  pthread_mutex_unlock(&boardLock);

  // Commit this thread's assigned starting choice
  localBoard[data->startRow][data->startCol] = data->startingValue;

  if (backtrackSimple(localBoard)) {

    // C: Lock the master board so we don't write over each other
    pthread_mutex_lock(&boardLock);
    if (!solutionFound) {
      solutionFound = true; // telling other threads

      // Copying our sol
      for (int r = 0; r < 25; r++) {
        for (int c = 0; c < 25; c++) {
          globalBoard[r][c] = localBoard[r][c];
        }
      }
    }
    pthread_mutex_unlock(&boardLock);
  }

  delete data;
  return NULL;
}

bool solveSudokuParallel(int board[25][25], int numThreads) {
  globalBoard = board;
  solutionFound = false;

  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 25; j++) {
      if (board[i][j] == 0) {

        std::vector<int> initialChoices;
        for (int k = 0; k < 25; k++) {
          if (!checkinRow(board, i, inputs[k]) &&
              !checkinCol(board, j, inputs[k]) &&
              !checkinBox(board, i, j, inputs[k])) {
            initialChoices.push_back(inputs[k]);
          }
        }

        // If no moves are possible right at the start, the puzzle is invalid
        if (initialChoices.empty())
          return false;

        std::vector<pthread_t> threadIds;

        // create a thread for each starting option (limited by the requested
        // thread count)
        for (size_t c = 0; c < initialChoices.size() && c < (size_t)numThreads;
             c++) {
          ThreadData *data = new ThreadData();
          data->startRow = i;
          data->startCol = j;
          data->startingValue = initialChoices[c];

          pthread_t thread;
          pthread_create(&thread, NULL, workerFunction, (void *)data);
          threadIds.push_back(thread);
        }

        // Wait for all threads to finish their work paths
        for (pthread_t thread : threadIds) {
          pthread_join(thread, NULL);
        }

        return solutionFound;
      }
    }
  }
  return checkIfBoardIsFilled(board);
}