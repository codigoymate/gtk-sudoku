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
	const unsigned get_selected_option() const;

private:
	/** Level radio buttons */
	Gtk::RadioButton *easy_option, *medium_option, *hard_option;
};
