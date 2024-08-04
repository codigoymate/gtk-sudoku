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

#include <sudoku.h>

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

/**
 * @brief Show the new game dialog and returns true if is accepted.
 * false if cancelled.
 * 
 * @param app Sudoku application ref.
 * @return true if the dialog is accepted.
 */
bool NewGameDialog::show(SudokuApp *app) {
	NewGameDialog *dialog;
	auto builder = Gtk::Builder::create_from_file("../ui/new-game-dialog.glade");
	builder->get_widget_derived("new-game-dialog", dialog);

	auto result = dialog->run();

	dialog->close();

	if (result == Gtk::RESPONSE_ACCEPT) {
		app->new_game(dialog->get_selected_option());
		return true;
	}
	return false;
}
