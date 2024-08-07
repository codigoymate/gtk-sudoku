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
			SudokuApp *app);
	
	/**
	 * @brief Show this window.
	 * 
	 * @param app Application context.
	 * @param parent Parent window.
	 */
	static void show(SudokuApp *app, Gtk::Window &parent);
private:
	SudokuApp *app; /** Application context. */
	Gtk::FlowBox *board_flow; /** Icon based list to show boards. */
	std::vector<Board> board_list; /** Logical board list. */

	/**
	 * @brief Load board list from collection and fills list flow.
	 * 
	 */
	void load_boards();
};
