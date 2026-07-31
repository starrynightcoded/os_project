#ifndef PARALLEL_SOLVER_H
#define PARALLEL_SOLVER_H

#include "Board.h"

// Solves the 9x9 board using multiple threads for the single-candidate
// filling phase (concurrency control via mutex), then falls back to
// sequential backtracking for anything left over.
bool solveParallel(Board &board, int numThreads = 3);

#endif