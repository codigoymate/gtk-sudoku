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
 * @param max_solutions maximum of solutions to find. -1 to all.
 * @return std::list<Board> list of solutions.
 */
std::list<Board> Solver::solve(const Board &board, const unsigned max_solutions) {
	std::list<Board> solutions;
	Board copy = board;
	solve(copy, solutions, max_solutions);
	return solutions;
}

/**
 * @brief Internal solve() function for recursive calls.
 * 
 * @param board Board to solve.
 * @param solutions solutions found.
 * @param max_solutions maximum of solutions to find. -1 to all.
 * @return true if all solutions were found.
 */
const bool Solver::solve(Board &board, std::list<Board> &solutions, const unsigned max_solutions) {
	auto i = get_next_empty_cell(board);

	if (i == board.get_size()) {
		solutions.push_back(board);

		if (solutions.size() == max_solutions) return true;
		return false;
	}

	auto s = board.get_width();

	for (unsigned v = 1; v <= s; v ++) {
		board.board[i].value = v;
		if (board.is_valid(i % s, std::floor(i / s))) {
			if (solve(board, solutions, max_solutions)) return true;
		}
		board.board[i].value = 0;

	}

	return false;
}

/**
 * @brief Returns the next position with value = 0 on the board
 * starting from the top left.
 */
const unsigned Solver::get_next_empty_cell(const Board &board) {
	for (unsigned i = 0; i < board.get_size(); i ++) {
		if (board.board[i].value) continue;
		return i;
	}

	return board.get_size();
}
