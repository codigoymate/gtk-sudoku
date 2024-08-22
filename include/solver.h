/**
 * @file solver.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Sudoku solver module.
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <board.h>

#include <list>

/**
 * @brief Solve a Sudoku board with backtracking algorithm.
 * Gets the all solutions.
 * 
 */
class Solver {
public:
	/**
	 * @brief Solve a Sudoku board and return the solutions.
	 * 
	 * @param board Board to solve.
	 * @param max_solutions maximum of solutions to find. -1 to all.
	 * @return std::list<Board> list of solutions.
	 */
	static std::list<Board> solve(const Board &board, const unsigned max_solutions);

private:
	/**
	 * @brief Internal solve() function for recursive calls.
	 * 
	 * @param board Board to solve.
	 * @param solutions solutions found.
	 * @param max_solutions maximum of solutions to find. -1 to all.
	 * @return true if all solutions were found.
	 */
	static const bool solve(Board &board, std::list<Board> &solutions, const unsigned max_solutions);
	
	/**
	 * @brief Returns the next position with value = 0 on the board
	 * starting from the top left.
	 */
	static const unsigned get_next_empty_cell(const Board &board);
};
