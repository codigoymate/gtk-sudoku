/**
 * @file board.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implemetation of board.h
 * @date 2024-07-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <board.h>

#include <iostream>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <assert.h>

using std::cout;
using std::endl;

void Board::print() const {
	for (unsigned y = 0; y < 9; y ++) {
		if (y % 3 == 0) cout << (y == 0 ? "" : " ------·------·-----") << endl;

		for (unsigned x = 0; x < 9; x ++) {
			if (x % 3 == 0) cout << (x == 0 ? " " : "|");

			if (get(x, y).value)
				cout << get(x, y).value << " ";
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
