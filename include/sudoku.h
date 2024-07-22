/**
 * @file sudoku.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Contains basic structures and algorithms to represent
 * the 9x9 Sudoku board.
 * @version 0.1
 * @date 2024-07-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <list>
#include <string>

/**
 * @brief Represents a cell in the Sudoku board.
 * 
 */
class Cell {
public:
	Cell() = default;

	unsigned value{}; /** Value of the cell (0 for empty cell). */
	bool fixed{}; /** True: Fixed value: algorithms should not
						change the value of this cell.*/
};

/**
 * @brief Represents the 9 x 9 Sudoku board.
 * 
 */
class Board {
public:
	Board() = default;

	/**
	 * @brief Copy constructor.
	 */
	Board(const Board &board);

	/**
	 * @brief Gets the cell at a given position.
	 * 
	 * @param x X coordinate of the cell.
	 * @param y Y coordinate of the cell.
	 * @return const Cell the cell at the given position.
	 */
	const Cell get(const unsigned x, const unsigned y) const;

	/**
	 * @brief Sets a cell at the given position.
	 * 
	 * @param x X coordinate of the cell.
	 * @param y Y coordinate of the cell. 
	 * @param cell the cell to set.
	 */
	void set(const unsigned x, const unsigned y, const Cell cell);

	/**
	 * @brief Checks a board position xy if its value does not repeat
	 * horizontally, vertically, or in the square area.
	 * 
	 * @param x X coordinate of the value.
	 * @param y Y coordinate of the value.
	 * @return true if the value fits.
	 * @return false if the value does not fit.
	 */
	const bool is_valid(const unsigned x, const unsigned y) const;

	/**
	 * @brief Returns true when the board is full.
	 */
	const bool full() const;

	/**
	 * @brief Generates n random values at random positions; valid and fixed.
	 * 
	 * @param n Number of values to generate
	 */
	void spawn(const unsigned n);

	/**
	 * @brief Resets the board with the original fixed numbers.
	 * 
	 */
	void reset();

	/**
	 * @brief Compares two boards.
	 * 
	 * @param board board to compare.
	 * @return true when they are equal.
	 * @return false when they are different.
	 */
	const bool operator==(const Board &board) const;

	/**
	 * @brief Compares two boards.
	 * 
	 * @param board board to compare.
	 * @return false when they are equal.
	 * @return true when they are different.
	 */
	const bool operator!=(const Board &board) const;

	/**
	 * @brief Solve a board and returns the list of solutions.
	 * 
	 * @param board board to solve.
	 * @return std::list<Board> list of solutions.
	 */
	static std::list<Board> solve(const Board &board);

	/**
	 * @brief Creates a board with random fixed numbers.
	 * 
	 * @param startNumbers The number of initial fixed numbers.
	 * @param solutions The number of solutions sought.
	 * @return Board The new board.
	 */
	static Board generate(const unsigned startNumbers, const unsigned solutions);

	/**
	 * @brief Returns the next empty cell counting from left to bottom.
	 * 
	 * @param board reference to the board
	 * @return const unsigned the position from 0 to 80.
	 */
	static const unsigned get_next_empty_cell(const Board &board);

	/**
	 * @brief Loads the board from an xml file.
	 * 
	 * @param path File path.
	 */
	void load(const std::string path);

	/**
	 * @brief Saves the board to an xml file.
	 * 
	 * @param path File path.
	 */
	void save(const std::string path);

private:

	/**
	 * @brief Generates a random value at a random position; valid and fixed.
	 * (Used by spawn(n))
	 */
	void spawn();

	/**
	 * @brief Solves the sudoku with Backtracking adding the solutions to
	 * a list.
	 * 
	 * @param board Reference to the initial board.
	 * @param solutions Reference to the list of solutions.
	 * @param max_solutions Maximum number of solutions.
	 * @param loop_counter Reference to the loop counter for when it doesn't find the solution.
	 * @return true if partially solved.
	 */
	static bool solve(Board board, std::list<Board> &solutions, const unsigned max_solutions,
		unsigned long &loop_counter);

	static Board generate(const Board &board, const unsigned solutions);

	Cell board[81]; /** The Sudoku board */
};
