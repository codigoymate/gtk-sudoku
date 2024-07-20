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
#include <vector>
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
	const bool isValid(const unsigned x, const unsigned y) const;

	/**
	 * @brief Returns true when the board is full.
	 */
	const bool full() const;

	/**
	 * @brief Checks the entire board to see if it is completely valid
	 * horizontally, vertically, or in the square area.
	 * 
	 * In case an error is found, it returns the coordinates through x and y.
	 * 
	 * @param x The x-coordinate where an error was found, if any.
	 * @param y The y-coordinate where an error was found, if any.
	 * @return true if all board is valid.
	 */
	const bool isAllValid(signed &x, signed &y) const;

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
	 * @brief Solves the sudoku with Backtracking adding the solutions to
	 * a list.
	 * 
	 * @param board Reference to the initial board.
	 * @param solutions Reference to the list of solutions.
	 * @param maxSolutions Maximum number of solutions.
	 * @param loopCounter Reference to the loop counter for when it doesn't find the solution.
	 * @return true if partially solved.
	 */
	static bool solve(Board &board, std::vector<Board> &solutions, const unsigned maxSolutions,
		unsigned long &loopCounter);

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
	static const unsigned getNextEmptyCell(const Board &board);

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
	 * @brief Returns true if a number from 1 to 9 does not repeat in the given array.
	 */
	const bool isLineValid(const unsigned line[]) const;

	/**
	 * @brief Returns true if a number from 1 to 9 does not repeat in the row
	 * at position Y.
	 */
	const bool isHValid(const unsigned y) const;

	/**
	 * @brief Returns true if a number from 1 to 9 does not repeat in the column
	 * at position X.
	 */
	const bool isVValid(const unsigned x) const;

	/**
	 * @brief Returns true if a number from 1 to 9 does not repeat in the area
	 * at the given X and Y position.
	 */
	const bool isAreaValid(const unsigned x, const unsigned y) const;

	/**
	 * @brief Generates a random value at a random position; valid and fixed.
	 * (Used by spawn(n))
	 */
	void spawn();

	static Board generate(Board board, const unsigned solutions);

	Cell board[81]; /** The Sudoku board */
};
