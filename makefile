all:
	g++ -c -std=c++11 sudoku_solver.cpp
	ar rsv sudoku_solver.a sudoku_solver.o

