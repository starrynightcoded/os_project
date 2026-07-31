#include <iostream>
#include "Board.h"
#include "SequentialSolver.h"
#include "ParallelSolver.h"
using namespace std;

int main() {
    int boardChoice = 0;
    int modeChoice = 0;

    cout << "Choose board size:" << endl;
    cout << "  1. 9x9" << endl;
    cout << "  2. 25x25" << endl;
    cout << "Enter choice: ";
    cin >> boardChoice;

    cout << endl << "Choose solving mode:" << endl;
    cout << "  1. Normal (sequential)" << endl;
    cout << "  2. Parallel (threads)" << endl;
    cout << "Enter choice: ";
    cin >> modeChoice;
    cout << endl;

    if (boardChoice == 1) {
        Board board;

        cout << "Initial board:" << endl;
        board.print();
        cout << endl;

        bool solved = false;
        if (modeChoice == 1) {
            cout << "Solving sequentially..." << endl;
            solved = solveSequential(board);
        } else if (modeChoice == 2) {
            cout << "Solving in parallel (3 threads)..." << endl;
            solved = solveParallel(board, 3);
        } else {
            cout << "Invalid mode choice." << endl;
            return 1;
        }

        cout << endl;
        cout << (solved ? "Board solved successfully!" : "Board could not be fully solved.") << endl;
        board.print();

    } else if (boardChoice == 2) {
        // 25x25 board + solvers will be implemented
        cout << "25x25 mode is handled in the Board25 / Solver25 files." << endl;
    } else {
        cout << "Invalid board choice." << endl;
    }

    return 0;
}