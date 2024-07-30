/**
 * @file generator.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of generator.h
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <generator.h>

#include <random>
#include <chrono>

#include <board.h>

#include <solver.h>

/**
 * @brief Random generator.
 * 
 */
std::default_random_engine rand_generator(std::chrono::system_clock::now().time_since_epoch().count());

/**
 * @brief Shuffle a vector.
 * 
 * @param v the vector.
 */
void shuffle(std::vector<unsigned> &v);

/**
 * @brief Generates a new Sudoku board.
 * 
 * @param hidden_numbers number of hidden values.
 * @param solutions number of solutions of the board.
 * @return Board the generated board.
 */
Board Generator::generate_board(const unsigned hidden_numbers, const unsigned solutions) {

	Board board = fill_board();

	std::vector<unsigned> positions(81);
    std::iota(positions.begin(), positions.end(), 0);
	shuffle(positions);

	while (hidden_count(board) < hidden_numbers) {
		auto p = positions.back();
		positions.pop_back();

		auto v = board.board[p].value;
		board.board[p].value = 0;

		if (Solver::solve(board, solutions + 1).size() > solutions) {

			// Rollback
			board.board[p].value = v;
			positions.insert(positions.begin(), p);
		}
	}

	// Fix the visible values
	for (unsigned i = 0; i < 81; i ++) if (board.board[i].value) board.board[i].fixed = true;

	return board;
}



/**
	 * @brief Returns the number of cells with the value = 0 of the board.
	 */
const unsigned Generator::hidden_count(const Board &board) {
	unsigned count = 0;
	for (unsigned i = 0; i < 81; i ++) if (!board.board[i].value) count ++;
	return count;
}

/**
 * @brief Generates a new fully board with randomized values.
 * The board is validated with the Sudoku's rules.
 * @return Board The generated board.
 */
Board Generator::fill_board() {

	Board board;

	// Squares
	for (unsigned s = 0; s < 9; s += 3) {
		// Numbers
		std::vector<unsigned> list = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		shuffle(list);
		for (unsigned y = s; y < s + 3; y ++) {
			for (unsigned x = s; x < s + 3; x ++) {
				board.set(x, y, { list.back(), false });
				list.pop_back();
			}
		}
	}

	return Solver::solve(board, 1).front();
}

/**
 * @brief Returns a randomly generated integer between min and max.
 */
const int Generator::rand_int(const int min, const int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rand_generator);
}

/**
 * @brief Shuffle a vector.
 * 
 * @param v the vector.
 */
void shuffle(std::vector<unsigned> &v) {
	for (unsigned i = 0; i < v.size(); i ++) {
		auto r = Generator::rand_int(0, v.size() - 1);
		auto tmp = v[i];
		v[i] = v[r];
		v[r] = tmp;
	}
}
