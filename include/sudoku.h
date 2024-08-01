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
#include <player.h>

class MainWindow;

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

	Player &get_player() { return player; }

	std::shared_ptr<MainWindow> get_main_window() const { return main_window; }

	/**
	 * @brief Start a new game.
	 * @param difficulty game difficulty.
	 */
	void new_game(const unsigned difficulty);

	/**
	 * @brief Save the current board to the player path.
	 * 
	 */
	void save_board();

	/**
	 * @brief Load the current board from the player path.
	 * 
	 */
	void load_board();

protected:
	/**
	 * @brief On game start.
	 * 
	 */
	void on_activate() override;

private:
	std::shared_ptr<MainWindow> main_window; /** < Main Window instance. */
	Board board{}, solved{}; /** < Board object. */
	Player player;
};
