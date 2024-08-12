/**
 * @file new-game-dialog.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief New game dialog and level selector.
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <gtkmm.h>

class SudokuApp;

/**
 * @brief New game dialog and level selector.
 * 
 */
class NewGameDialog : public Gtk::Dialog {
public:
	/**
	 * @brief Construct a new New Game Dialog
	 */
	NewGameDialog(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const& builder);

	/**
	 * @brief Returns the selected level difficulty. 
	 */
	const unsigned get_selected_level() const;

	/**
	 * @brief Returns the selected level size.
	 */
	const unsigned get_selected_size() const;

	/**
	 * @brief Show the new game dialog and returns true if is accepted.
	 * false if cancelled.
	 * 
	 * @param app Sudoku application ref.
	 * @return true if the dialog is accepted.
	 */
	static bool show(SudokuApp *app);

private:
	/** Radio buttons */
	Gtk::RadioButton *easy_option, *medium_option, *hard_option;
	Gtk::RadioButton *x81_option, *x16_option;
};
