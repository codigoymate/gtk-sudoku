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
#include <iostream>

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
 * @param size the size of the board.
 * @return Board the generated board.
 */
Board Generator::generate_board(const unsigned hidden_numbers, const unsigned solutions,
			const unsigned size) {

	std::cout << "Randomize board. ";
	Board board = fill_board(size);

	std::cout << "id: " << board.get_id() << std::endl;

	std::cout << "Generating id: " << board.get_id() << " (HN: " << hidden_numbers <<
			", Sol: " << solutions << ")." << std::endl; 

	std::vector<unsigned> positions(size);
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

	std::cout << "Fixing visible values." << std::endl;
	// Fix the visible values
	for (unsigned i = 0; i < size; i ++) if (board.board[i].value) board.board[i].fixed = true;

	return board;
}



/**
	 * @brief Returns the number of cells with the value = 0 of the board.
	 */
const unsigned Generator::hidden_count(const Board &board) {
	unsigned count = 0;
	for (unsigned i = 0; i < board.get_size(); i ++) if (!board.board[i].value) count ++;
	return count;
}

/**
 * @brief Generates a new fully board with randomized values.
 * The board is validated with the Sudoku's rules.
 * @param size the size of the board.
 * @return Board The generated board.
 */
Board Generator::fill_board(const unsigned size) {

	Board board(size);

	auto sz = size == 81 ? 9 : 4;
	auto step = size == 81 ? 3 : 2;

	// Squares
	for (unsigned s = 0; s < sz; s += step) {
		// Numbers
		std::vector<unsigned> list = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		if (size != 81) list = { 1, 2, 3, 4 };

		shuffle(list);
		for (unsigned y = s; y < s + step; y ++) {
			for (unsigned x = s; x < s + step; x ++) {
				board.set(x, y, { list.back(), false });
				list.pop_back();
			}
		}
	}


	auto solutions = Solver::solve(board, 1);
	
	// Considere 8x8 boards no solutions recall fill_board()
	if (solutions.size() == 0) {
		return fill_board(size);
	}

	return solutions.front();
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
