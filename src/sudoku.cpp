/**
 * @file sudoku.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implemetation of sudoku.h
 * @date 2024-07-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <sudoku.h>

#include <iostream>
#include <random>
#include <chrono>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <assert.h>

using std::cout;
using std::endl;

std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
int rand_int(int min, int max);

/**
 * @brief Prints the Sudoku board.
 * 
 * @param board The Sudoku board to print.
 */
void print_board(const Board board) {
	for (unsigned y = 0; y < 9; y ++) {
		if (y % 3 == 0) cout << (y == 0 ? "" : " ------·------·-----") << endl;

		for (unsigned x = 0; x < 9; x ++) {
			if (x % 3 == 0) cout << (x == 0 ? " " : "|");

			if (board.get(x, y).value)
				cout << board.get(x, y).value << " ";
			else cout << "  ";
		}
		cout << endl;
	}
}

/**
 * @brief Copy constructor for Board.
 * 
 * @param board The board to copy.
 */
Board::Board(const Board &board) {
	for (unsigned i = 0; i < 81; i ++) this->board[i] = board.board[i];
}

/**
 * @brief Gets the cell at a given position.
 * 
 * @param x X coordinate of the cell.
 * @param y Y coordinate of the cell.
 * @return const Cell The cell at the given position.
 */
const Cell Board::get(const unsigned x, const unsigned y) const {
	return board[y * 9 + x];
}

/**
 * @brief Sets a cell at the given position.
 * 
 * @param x X coordinate of the cell.
 * @param y Y coordinate of the cell. 
 * @param cell The cell to set.
 */
void Board::set(const unsigned x, const unsigned y, const Cell cell) {
	board[y * 9 + x] = cell;
}

/**
 * @brief Checks if a board position (x, y) is valid, meaning its value does not repeat
 * horizontally, vertically, or in the 3x3 area.
 * 
 * @param x X coordinate of the value.
 * @param y Y coordinate of the value.
 * @return true if the value fits.
 * @return false if the value does not fit.
 */
const bool Board::is_valid(const unsigned x, const unsigned y) const {

	auto value = get(x, y).value;

	for (unsigned xx = 0; xx < 9; xx ++) {
		if (xx == x) continue;
		if (get(xx, y).value == 0) continue;
		if (get(xx, y).value == value) return false;
	}

	for (unsigned yy = 0; yy < 9; yy ++) {
		if (yy == y) continue;
		if (get(x, yy).value == 0) continue;
		if (get(x, yy).value == value) return false;
	}

	for (unsigned yy = (y / 3) * 3; yy < (y / 3) * 3 + 3; yy ++) {
		for (unsigned xx = (x / 3) * 3; xx < (x / 3) * 3 + 3; xx ++) {
			if (yy == y && xx == x) continue;
			if (get(xx, yy).value == 0) continue;
			if (get(xx, yy).value == value) return false;
		}
	}

	return true;
}

/**
 * @brief Returns true when the board is full.
 * 
 * @return true if the board is full.
 * @return false if the board is not full.
 */
const bool Board::full() const {
	for (signed i = 80; i >= 0; i --) if (board[i].value == 0) return false;
	return true;
}

/**
 * @brief Generates a random value at a random position; valid and fixed.
 * 
 */
void Board::spawn() {
	auto pos = rand_int(0, 80);
	if (board[pos].value) {
		spawn(); return;
	}

	board[pos].value = rand_int(1, 9);
	if (!is_valid(pos % 9, floor(pos / 9))) {
		board[pos].value = 0;
		spawn(); return;
	}

	board[pos].fixed = true;
}

/**
 * @brief Generates n random values at random positions; valid and fixed.
 * 
 * @param n Number of values to generate.
 */
void Board::spawn(const unsigned n) {
	for (unsigned i = 0; i < n; i ++) spawn();
}

/**
 * @brief Compares two boards.
 * 
 * @param board Board to compare.
 * @return true when they are equal.
 * @return false when they are different.
 */
const bool Board::operator==(const Board &board) const {
	for (unsigned i = 0; i < 81; i ++) {
		if (this->board[i].value != board.board[i].value) return false;
	}
	return true;
}

/**
 * @brief Compares two boards.
 * 
 * @param board Board to compare.
 * @return false when they are equal.
 * @return true when they are different.
 */
const bool Board::operator!=(const Board &board) const {
	return !(*this == board);
}

/**
 * @brief Resets the board with the original fixed numbers.
 * 
 */
void Board::reset() {
	for (unsigned i = 0; i < 81; i ++) if (!board[i].fixed) board[i].value = 0;
}

/**
 * @brief Solves the Sudoku using Backtracking and adds the solutions to
 * a list.
 * 
 * @param board Reference to the initial board.
 * @param solutions Reference to the list of solutions.
 * @param max_solutions Maximum number of solutions.
 * @param loop_counter Reference to the loop counter for when it doesn't find the solution.
 * @return true if partially solved.
 */
bool Board::solve(Board &board, std::vector<Board> &solutions, const unsigned max_solutions, unsigned long &loop_counter) {

	loop_counter ++;

	if (loop_counter >= 1000000 && solutions.empty()) {
		return true;
	}

	unsigned i = get_next_empty_cell(board);

	if (i == 81) {
		Board newBoard = board;
        if (solutions.size() < max_solutions) {
            solutions.push_back(newBoard);
        }
        return solutions.size() == max_solutions;
	}

	for (unsigned v = 1; v <= 9; v ++) {
		board.board[i].value = v;
		if (board.is_valid(i % 9, floor(i / 9))) {
			if (solve(board, solutions, max_solutions, loop_counter)) return true;
		}
	}

	board.board[i].value = 0;

	return false;
}

/**
 * @brief Creates a board with random fixed numbers.
 * 
 * @param startNumbers The number of initial fixed numbers.
 * @param solutions The number of solutions sought.
 * @return Board The new board.
 */
Board Board::generate(const unsigned startNumbers, const unsigned solutions) {
	Board board;
	cout << "Spawn " << startNumbers << endl;
	board.spawn(startNumbers);
	return generate(board, solutions);
}

Board Board::generate(Board board, const unsigned solutionCount) {
	std::vector<Board> solutions;
	Board solving = board;
	cout << "Add 1" << endl;
	solving.spawn(1);
	Board solving_added = solving;
	cout << "Solving ..." << endl;
	unsigned long loop_counter = 0;
	Board::solve(solving, solutions, solutionCount + 1, loop_counter);
	cout << "Solutions found: " << solutions.size() << endl;
	if (solutions.size() == solutionCount) {
		cout << "Done." << endl;
		return solving_added;
	} else if (solutions.size() < solutionCount) {
		return generate(board, solutionCount);
	} else {
		return generate(solving_added, solutionCount);
	}
}

/**
 * @brief Gets the next empty cell from the board.
 * 
 * @param board The board to check.
 * @return unsigned The index of the next empty cell.
 */
const unsigned Board::get_next_empty_cell(const Board &board) {
	for (unsigned i = 0; i < 81; i ++) {
		if (board.board[i].value) continue;
		return i;
	}

	return 81;
}

/**
 * @brief Loads the board from an xml file.
 * 
 * @param path Path of the file.
 */
void Board::load(const std::string path) {
	LIBXML_TEST_VERSION

	auto doc = xmlReadFile(path.c_str(), "UTF-8", 0);
	assert(doc != nullptr && "Sudoku board: Cannot read xml file.");

	auto root_node = xmlDocGetRootElement(doc);

	xmlNode *cur_node = nullptr;

	for (cur_node = root_node->children; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE) {
			if (xmlStrcmp(cur_node->name, BAD_CAST "solved") == 0) {
				std::string data = (char *) xmlNodeGetContent(cur_node);
				unsigned index = 0;
				for (unsigned i = 0; i < data.size() ; i ++) {
					if (std::isdigit(data[i])) {
						board[index].value = data[i] - '0';
						index ++;
					}
				}
			}
		} else if (cur_node->type == XML_TEXT_NODE) {
			std::string data = (char *) cur_node->content;

			unsigned index = 0;
			for (unsigned i = 0; i < data.size() ; i ++) {
				if (std::isdigit(data[i])) {
					board[index].value = data[i] - '0';
					board[index].fixed = board[index].value ? true : false; 
					index ++;
				}
			}
		}
	}
	
}

/**
 * @brief Saves the board to an xml file.
 * 
 * @param path Path of the file.
 */
void Board::save(const std::string path) {
	LIBXML_TEST_VERSION

	 // Crear un nuevo documento XML
	auto doc = xmlNewDoc(BAD_CAST "1.0");
	auto root_node = xmlNewNode(nullptr, BAD_CAST "sudoku-board");
	xmlDocSetRootElement(doc, root_node);

	std::string data = "\n\t";

	for (unsigned y = 0; y < 9; y ++) {
		for (unsigned x = 0; x < 9; x ++) {
			auto value = 0;
			if (get(x, y).fixed) value = get(x, y).value;
			data += std::to_string(value) + " ";
		}
		data += "\n\t";
	}

	xmlNodeSetContent(root_node, BAD_CAST data.c_str());

	auto solved = xmlNewNode(nullptr, BAD_CAST "solved");
	xmlAddChild(root_node, solved);

	data = "\n\t";
	for (unsigned y = 0; y < 9; y ++) {
		for (unsigned x = 0; x < 9; x ++) {
			data += std::to_string(get(x, y).value) + " ";
		}
		data += "\n\t";
	}

	xmlNodeSetContent(solved, BAD_CAST data.c_str());

	auto result = xmlSaveFormatFileEnc(path.c_str(), doc, "UTF-8", 1);
	assert(result != -1 && "Sudoku board: Cannot save xml file.");

	xmlFreeDoc(doc);
	xmlCleanupParser();
}

/**
 * @brief Generates a random integer between min and max.
 * 
 * @param min The minimum value.
 * @param max The maximum value.
 * @return int The generated random integer.
 */
int rand_int(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(generator);
}
