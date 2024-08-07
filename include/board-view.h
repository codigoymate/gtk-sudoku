/**
 * @file board-view.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Basic visual board representation.
 * @date 2024-08-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <gtkmm.h>

#include <board.h>

/**
 * @brief Widget to show a Sudoku board. 
 * 
 */
class BoardView: public Gtk::DrawingArea {
public:
	/**
	 * @brief Construct a new BoardView
	 * 
	 * @param obj base object.
	 * @param builder ui builder.
	 * @param board Board to draw.
	 */
	BoardView(const Board &board);


	/**
	 * @brief On board draw.
	 * 
	 * @param cr Cairo drawing context.
	 * @return true ever.
	 */
	bool on_area_draw(const Cairo::RefPtr<Cairo::Context>& cr);

private:
	Board board;
};
