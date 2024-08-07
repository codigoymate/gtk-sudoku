/**
 * @file board.h
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

	friend class Solver;
	friend class Generator;

	/**
	 * @brief Construct a new Board object
	 * Generates an identificator number to persist the board.
	 */
	Board();

	/**
	 * @brief Copy constructor.
	 */
	Board(const Board &board);

	/**
	 * @brief Returns id board in format yyyyMMddhhmmss. 
	 */
	const std::string get_id() const { return id; }

	/**
	 * @brief Sets de id in format yyyyMMddhhmmss. 
	 */
	void set_id(const std::string id) { this->id = id; }

	/**
	 * @brief Get the difficulty level.
	 */
	const std::string get_difficulty() const { return difficulty; }

	/**
	 * @brief Set the difficulty level.
	 */
	void set_difficulty(const std::string difficulty) { this->difficulty = difficulty; }

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
	 * @brief Returns true when the board is clear.
	 */
	const bool empty() const;

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

	/**
	 * @brief Returns the formatted name from board id. 
	 */
	const std::string get_name() const;

	/**
	 * @brief Return true if board is marked solved. 
	 */
	const bool is_solved_mark() const { return solved_mark; }

	/**
	 * @brief Set solved to mark "solved" in collection.
	 * 
	 * @param sm 
	 */
	void set_solved_mark(const bool sm) { solved_mark = true; }

	void print() const;

private:
	std::string id; /** id of board in format yyyyMMddhhmmss */
	std::string difficulty; /** Difficulty level */
	bool solved_mark{}; /** Mark true when board is solved. */

	Cell board[81]; /** The Sudoku board */
};
