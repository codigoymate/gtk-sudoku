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
#include <chrono>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <assert.h>

using std::cout;
using std::endl;

void Board::print() const {
	if (this->get_size() == 81) {
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
	} else {
		for (unsigned y = 0; y < 4; y ++) {
			if (y % 2 == 0) cout << (y == 0 ? "" : " ----·----") << endl;

			for (unsigned x = 0; x < 4; x ++) {
				if (x % 2 == 0) cout << (x == 0 ? " " : "|");

				if (get(x, y).value)
					cout << get(x, y).value << " ";
				else cout << "  ";
			}
			cout << endl;
		}
	}
	cout << "Board id: " << id << endl;
}

/**
 * @brief Construct a new Board object
 * Generates an identificator number to persist the board.
 * Identificator format: yyyyMMddhhmmss
 */
Board::Board() : Board(81) {}

/**
 * @brief Construct a new Board object
 * Generates an identificator number to persist the board.
 * Identificator format: yyyyMMddhhmmss
 */
Board::Board(const unsigned size) {
	board = std::vector<Cell>(size);

	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::tm* now_tm = std::localtime(&now_c);

	id = std::to_string(now_tm->tm_year + 1900);
	auto month = now_tm->tm_mon + 1;
	id += (month < 10 ? "0" : "") + std::to_string(month);
	auto day = now_tm->tm_mday;
	id += (day < 10 ? "0" : "") + std::to_string(day);

	auto hour = now_tm->tm_hour;
	id += (hour < 10 ? "0" : "") + std::to_string(hour);
	auto minute = now_tm->tm_min;
	id += (minute < 10 ? "0" : "") + std::to_string(minute);
	auto second = now_tm->tm_sec;
	id += (second < 10 ? "0" : "") + std::to_string(second);
}

/**
 * @brief Copy constructor for Board.
 * 
 * @param board The board to copy.
 */
Board::Board(const Board &board) {
	this->id = board.id;
	this->difficulty = board.difficulty;
	this->solved_mark = board.solved_mark;
	this->board = std::vector<Cell>(board.get_size());
	for (unsigned i = 0; i < this->board.size(); i ++) this->board[i] = board.board[i];
}

/**
 * @brief Gets the cell at a given position.
 * 
 * @param x X coordinate of the cell.
 * @param y Y coordinate of the cell.
 * @return const Cell The cell at the given position.
 */
const Cell Board::get(const unsigned x, const unsigned y) const {
	if (get_size() == 81) return board[y * 9 + x];
	return board[y * 4 + x];
}

/**
 * @brief Sets a cell at the given position.
 * 
 * @param x X coordinate of the cell.
 * @param y Y coordinate of the cell. 
 * @param cell The cell to set.
 */
void Board::set(const unsigned x, const unsigned y, const Cell cell) {
	if (get_size() == 81) board[y * 9 + x] = cell;
	else board[y * 4 + x] = cell;
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

	auto s = get_size() == 81 ? 9 : 4;
	auto b = get_size() == 81 ? 3 : 2;

	for (unsigned xx = 0; xx < s; xx ++) {
		if (xx == x) continue;
		if (get(xx, y).value == 0) continue;
		if (get(xx, y).value == value) return false;
	}

	for (unsigned yy = 0; yy < s; yy ++) {
		if (yy == y) continue;
		if (get(x, yy).value == 0) continue;
		if (get(x, yy).value == value) return false;
	}

	for (unsigned yy = (y / b) * b; yy < (y / b) * b + b; yy ++) {
		for (unsigned xx = (x / b) * b; xx < (x / b) * b + b; xx ++) {
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
	for (signed i = get_size() - 1; i >= 0; i --) if (board[i].value == 0) return false;
	return true;
}

/**
 * @brief Returns true when the board is clear.
 */
const bool Board::empty() const {
	for (unsigned i = 0; i < get_size(); i ++) if (board[i].value) return false;
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
	for (unsigned i = 0; i < get_size(); i ++) {
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
	for (unsigned i = 0; i < get_size(); i ++) if (!board[i].fixed) board[i].value = 0;
	solved_mark = false;
}

/**
 * @brief Loads the board from an xml file.
 * 
 * @param path Path of the file.
 */
void Board::load(const std::string path) {
	LIBXML_TEST_VERSION

	std::cout << "Loading board: " << path << "." << std::endl;

	auto doc = xmlReadFile(path.c_str(), "UTF-8", 0);
	assert(doc != nullptr && "Sudoku board: Cannot read xml file.");

	auto root_node = xmlDocGetRootElement(doc);

	this->id = std::string((char *)xmlGetProp(root_node, BAD_CAST "id"));
	auto ssize = (char *)xmlGetProp(root_node, BAD_CAST "size");
	unsigned s = 81; // Default value if property not found (prev. versions)
	if (ssize) s = std::atoi(ssize);
	board = std::vector<Cell>(s);
	this->difficulty = std::string((char *)xmlGetProp(root_node, BAD_CAST "difficulty"));
	this->solved_mark = xmlStrcmp(xmlGetProp(root_node, BAD_CAST "solved"), BAD_CAST "true") == 0;

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

	xmlNewProp(root_node, BAD_CAST "id", BAD_CAST this->id.c_str());
	xmlNewProp(root_node, BAD_CAST "size", BAD_CAST std::to_string(this->get_size()).c_str());
	xmlNewProp(root_node, BAD_CAST "difficulty", BAD_CAST this->difficulty.c_str());
	xmlNewProp(root_node, BAD_CAST "solved", BAD_CAST (solved_mark ? "true" : "false"));

	std::string data = "\n\t";

	auto s = get_size() == 81 ? 9 : 4;

	for (unsigned y = 0; y < s; y ++) {
		for (unsigned x = 0; x < s; x ++) {
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
	for (unsigned y = 0; y < s; y ++) {
		for (unsigned x = 0; x < s; x ++) {
			data += std::to_string(get(x, y).value) + " ";
		}
		data += "\n\t";
	}

	xmlNodeSetContent(solved, BAD_CAST data.c_str());

	std::cout << "Saving board: " << path << "." << std::endl;
	auto result = xmlSaveFormatFileEnc(path.c_str(), doc, "UTF-8", 1);

	assert(result != -1 && "Sudoku board: Cannot save xml file.");

	xmlFreeDoc(doc);
	xmlCleanupParser();
}

/**
 * @brief Returns the formatted name from board id. 
 */
const std::string Board::get_name() const {
	if (id == "") return "";
	return id.substr(4, 2) + "-" + id.substr(6, 2) + "-" + id.substr(0, 4)
			+ " " + id.substr(8, 2) + ":" + id.substr(10, 2) + ":" + id.substr(12, 2);
}
