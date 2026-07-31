CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread -Iinclude

SRC = src/main.cpp src/Board.cpp src/SequentialSolver.cpp src/ParallelSolver.cpp
OUT = sudoku

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
