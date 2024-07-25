/**
 * @file solver.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of solver.h
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <solver.h>

#include <cmath>

/**
 * @brief Solve a Sudoku board and return the solutions.
 * 
 * @param board Board to solve.
 * @param max_solutions maximum of solutions to find.
 * @return std::list<Board> list of solutions.
 */
std::list<Board> Solver::solve(const Board &board, const unsigned max_solutions) {
	std::list<Board> solutions;
	solve(board, solutions, max_solutions);
	return solutions;
}

/**
 * @brief Internal solve() function for recursive calls.
 * 
 * @param board Board to solve.
 * @param solutions solutions found.
 * @param max_solutions maximum of solutions to find.
 * @return true if all solutions were found.
 */
const bool Solver::solve(Board board, std::list<Board> &solutions, const unsigned max_solutions) {
	auto i = get_next_empty_cell(board);

	if (i == 81) {

		if (!solutions.empty()) {
			if (board == solutions.front()) return true;
			if (solutions.size() == max_solutions) return true;
		}

		solutions.push_back(board);
		return false;
	}

	for (unsigned v = 1; v <= 9; v ++) {
		board.board[i].value = v;
		if (board.is_valid(i % 9, std::floor(i / 9))) {
			if (solve(board, solutions, max_solutions)) return true;
		}
	}

	return false;
}

/**
 * @brief Returns the next position with value = 0 on the board
 * starting from the top left.
 */
const unsigned Solver::get_next_empty_cell(const Board &board) {
	for (unsigned i = 0; i < 81; i ++) {
		if (board.board[i].value) continue;
		return i;
	}

	return 81;
}
