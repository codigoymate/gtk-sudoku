/**
 * @file collection-window.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Show collection of games played and current.
 * @date 2024-08-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <gtkmm.h>

class SudokuApp;
class Board;
class WelcomeWindow;

/**
 * @brief Collection window for games played.
 * 
 */
class CollectionWindow: public Gtk::Window {
public:
	/**
	 * @brief Construct a new CollectionWindow
	 */
	CollectionWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder,
			SudokuApp *app, WelcomeWindow *ww);
	
	/**
	 * @brief Show this window.
	 * 
	 * @param app Application context.
	 * @param parent Parent window.
	 */
	static void show(SudokuApp *app, WelcomeWindow *ww);
private:
	SudokuApp *app; /** Application context. */
	WelcomeWindow *welcomeWindow; /** Parent Welcome Window. */
	Gtk::FlowBox *board_flow; /** Icon based list to show boards. */
	Gtk::Button *play_button, *remove_button; /** Control buttons. */
	std::vector<Board> board_list; /** Logical board list. */

	/**
	 * @brief Load board list from collection and fills list flow.
	 * 
	 */
	void load_boards();

	/**
	 * @brief Sort the board list from most recent to old.
	 * 
	 */
	void sort_boards();

	/**
	 * @brief Selection change event
	 * 
	 */
	void board_flow_selection_changed();

	/**
	 * @brief Play button clicked event.
	 * 
	 */
	void play_button_clicked();

	/**
	 * @brief Remove button clicked event.
	 * 
	 */
	void remove_button_clicked();

	/**
	 * @brief Update some controls of the window.
	 * 
	 */
	void update();
};
