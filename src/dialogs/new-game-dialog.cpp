/**
 * @file new-game-dialog.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of new-game-dialog.h
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <dialogs/new-game-dialog.h>

/**
 * @brief Construct a new New Game Dialog
 */
NewGameDialog::NewGameDialog(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const& builder) : Gtk::Dialog(obj) {
	builder->get_widget("easy-option", easy_option);
	builder->get_widget("medium-option", medium_option);
	builder->get_widget("hard-option", hard_option);
}

/**
 * @brief Returns the selected level difficulty. 
 */
const unsigned NewGameDialog::get_selected_option() const {

	if (easy_option->get_active()) return 0;
	if (medium_option->get_active()) return 1;

	return 2;
}
