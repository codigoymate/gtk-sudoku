/**
 * @file board-area.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Drawing area for Sudoku board.
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <gtkmm.h>
#include <cairomm/context.h>

class SudokuApp;

/**
 * @brief BoardArea class.
 * 
 */
class BoardArea: public Gtk::DrawingArea {
public:
	/**
	 * @brief Construct a new Board Area object
	 */
	BoardArea(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app);

	/**
	 * @brief Set selected cell coords for highlight cell.
	 * x = -1 and y = -1 for no cell selected.
	 * 
	 * @param x x coord for selected cell.
	 * @param y y coord for selected cell.
	 */
	void select(const int x, const int y) { sel_x = x; sel_y = y; }

	/**
	 * @brief Set selected cell coords for highlight cell.
	 * x = -1 and y = -1 for no cell selected.
	 * 
	 * @param x x coord for selected cell.
	 * @param y y coord for selected cell.
	 * @param error true if the selected cell marks an error.
	 */
	void select(const int x, const int y, const bool error) {
		sel_x = x; sel_y = y; this->error = error;
	}

private:
	SudokuApp *app; /** < Application instance. */

	/**
	 * @brief On board draw.
	 * 
	 * @param cr Cairo drawing context.
	 * @return true ever.
	 */
	bool on_area_draw(const Cairo::RefPtr<Cairo::Context>& cr);

	/**
	 * @brief On board click.
	 * 
	 * @param event Mouse button event.
	 * @return true to leave the others handlers.
	 */
	bool on_area_click(GdkEventButton *event);

	/**
	 * @brief On key press.
	 * 
	 * @param event Keyboard event.
	 * @return true to leave the others handlers.
	 */
	bool on_area_key_press(GdkEventKey *event);

	int sel_x, sel_y; /** < Selected cell coord. */
	bool error{};
};
