/**
 * @file sudoku.h
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

#include <board.h>

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
	 * @return Board& Sudoku actual board.
	 */
	Board &get_board() { return board; }
	
	/**
	 * @brief Get the solved board.
	 * 
	 * @return Board& solved board.
	 */
	Board &get_solved() { return solved; }

	std::shared_ptr<MainWindow> get_main_window() const { return main_window; }

	/**
	 * @brief Start a new game.
	 * 
	 */
	void new_game();

protected:
	/**
	 * @brief On game start.
	 * 
	 */
	void on_activate() override;

private:
	std::shared_ptr<MainWindow> main_window; /** < Main Window instance. */
	Board board{}, solved{}; /** < Board object. */
};
