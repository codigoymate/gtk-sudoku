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
 * @param visible_numbers expected visible values.
 * @param solutions number of solutions of the board.
 * @param size the size of the board.
 * @return Board the generated board.
 */
Board Generator::generate_board(const unsigned vn, const unsigned solutions,
			const unsigned size) {

	std::cout << "Randomize board. ";
	Board board = fill_board(size);

	std::cout << "id: " << board.get_id() << std::endl;

	std::cout << "Generating id: " << board.get_id() << " (VN: " << vn <<
			", Sol: " << solutions << ")." << std::endl; 

	Board generated;
	generate_board(board, generated, vn, solutions);

	std::cout << "Fixing visible values." << std::endl;
	// Fix the visible values
	for (unsigned i = 0; i < size; i ++)
		if (generated.board[i].value) 
			generated.board[i].fixed = true;

	return generated;
}

/**
 * @brief Internal recursive method to generate a Sudoku board.
 * 
 * @param generating Initial board to start removing numbers from.
 * @param generated Resulting board.
 * @param vn Number of visible numbers.
 * @param solutions Expected number of solutions.
 * @return true When a board meeting the conditions is found.
 * @return false The board does not meet the conditions and continues searching.
 */
const bool Generator::generate_board(Board generating, Board &generated,
			const unsigned vn, const unsigned solutions) {
	std::vector<unsigned> positions;

	// Load visible positions
	for (unsigned i = 0; i < generating.get_size(); i ++)
		if (generating.board[i].value) 
			positions.push_back(i);

	if (positions.size() <= vn) {
		generated = generating;
		return true;
	}


	// Shuffle visible positions
	shuffle(positions);

	for (auto p : positions) {
		auto v = generating.board[p].value;
		generating.board[p].value = 0;
		auto sc = Solver::solve(generating, solutions + 1).size();
		if (sc <= solutions) {
			if (generate_board(generating, generated, vn, solutions)) return true;
		}
		generating.board[p].value = v;
		
	}

	return false;
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

	auto sz = board.get_width();
	auto step = board.get_sw();

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
