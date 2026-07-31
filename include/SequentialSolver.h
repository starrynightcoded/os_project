#ifndef SEQUENTIAL_SOLVER_H
#define SEQUENTIAL_SOLVER_H

#include "Board.h"

// Solves the board normally (single thread): repeated single-candidate
// filling, then backtracking for whatever is left. Returns true if solved.
bool solveSequential(Board &board);

#endif