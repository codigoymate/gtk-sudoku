/**
 * @file main-menu.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Sudoku main menu.
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <gtkmm.h>

class SudokuApp;

/**
 * @brief Sudoku Main Menu class.
 * 
 */
class MainMenu: public Gtk::MenuBar {
public:
	/**
	 * @brief Construct a new Main Menu object.
	 */
	MainMenu(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app);

private:

	/**
	 * @brief On New Game item click.
	 * 
	 */
	void menu_new_game() const;

	/**
	 * @brief On Check board item click;
	 * 
	 */
	void menu_check_board() const;

	/**
	 * @brief On Check welcome window item click;
	 * 
	 */
	void menu_welcome_window() const;

	/**
	 * @brief On Quit Game item click.
	 * 
	 */
	void menu_quit() const;

	SudokuApp *app; /** Application instance. */
};
