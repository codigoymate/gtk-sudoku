/**
 * @file generator.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Sudoku generator module. 
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

class Board;

/**
 * @brief Board generator for Sudoku game.
 * Generates boards with 24 or more visible numbers.
 * The generator is basic and might cause problems with fewer numbers.
 * (Always considering a single solution)
 */
class Generator {
public:

	/**
	 * @brief Generates a new Sudoku board.
	 * 
	 * @param hidden_numbers number of hidden values.
	 * @param solutions number of solutions of the board.
 	 * @param size the size of the board.
	 * @return Board the generated board.
	 */
	static Board generate_board(const unsigned hidden_numbers, const unsigned solutions,
		const unsigned size);

	/**
	 * @brief Returns a randomly generated integer between min and max.
	 */
	static const int rand_int(const int min, const int max);

private:
	/**
	 * @brief Generates a new fully board with randomized values.
	 * The board is validated with the Sudoku's rules.
 	 * @param size the size of the board.
	 * @return Board The generated board.
	 */
	static Board fill_board(const unsigned size);

	/**
	 * @brief Returns the number of cells with the value = 0 of the board.
	 */
	static const unsigned hidden_count(const Board &board); 
};
