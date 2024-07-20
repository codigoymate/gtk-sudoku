/**
 * @file app.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Sudoku Application.
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <gtkmm.h>

class MainWindow;
class Board;

/**
 * @brief Sudoku Application class.
 * 
 */
class SudokuApp: public Gtk::Application {
public:
	/**
	 * @brief Construct a new Sudoku App object.
	 */
	SudokuApp(int argc, char *argv[]);

	/**
	 * @brief Get the Board object.
	 * 
	 * @return std::shared_ptr<Board> Pointer to Sudoku Board.
	 */
	std::shared_ptr<Board> getBoard() { return board; }

protected:
	/**
	 * @brief On game start.
	 * 
	 */
	void on_activate() override;

private:
	std::shared_ptr<MainWindow> main_window; /** < Main Window instance. */
	std::shared_ptr<Board> board; /** < Board instance. */
};
