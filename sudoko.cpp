#include "board_25.h"
#include "helper_func.h"
#include "parallel_solver.h"
#include <chrono>
#include <iostream>

using namespace std;
// taken from lab task 8 starter code
uint64_t getMillisecondsSinceEpoch() {
  uint64_t milliseconds = 0;
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  std::chrono::system_clock::duration duration_since_epoch =
      now.time_since_epoch();
  std::chrono::milliseconds millis =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          duration_since_epoch);
  milliseconds = millis.count();
  return milliseconds;
}
int main() {
  // loadBoard25();
  // // printBoard(board);
  // // std::cout << "Solving 25 x 25 board sequencially via backtracking"
  // //           << std::endl;
  // // if (backtrack(board)) {
  // //   std::cout << "Successfully solved after backtracking ! Printing board:
  // "
  // //             << std::endl;
  // //   printBoard(board);
  // // }

  // if (solveSudokuParallel(board, 8)) {
  //   std::cout << "Solved 25 x 25 board parallelly by backtracking : \n";

  //   printBoard(board);
  // }

  // Sequential
  loadBoard25();
  uint64_t startSeq = getMillisecondsSinceEpoch();
  backtrack(board);
  uint64_t endSeq = getMillisecondsSinceEpoch();
  uint64_t seqTime = endSeq - startSeq;

  // Parallel
  loadBoard25(); // Reload the unsolved board
  uint64_t startPar = getMillisecondsSinceEpoch();
  solveSudokuParallel(board, 8);
  uint64_t endPar = getMillisecondsSinceEpoch();
  uint64_t parTime = endPar - startPar;

  if (seqTime < parTime) {
    std::cout << "Sequential solver is " << (parTime - seqTime) / 1000.0
              << " seconds faster than parallel solver.\n";
  } else if (parTime < seqTime) {
    std::cout << "Parallel solver is " << (seqTime - parTime) / 1000.0
              << " seconds faster than sequential solver.\n";
  } else {
    std::cout << "Both solvers took the same time.\n";
  }

  return 0;
}