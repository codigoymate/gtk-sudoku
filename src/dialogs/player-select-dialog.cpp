/**
 * @file player-select-dialog.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of player-select-dialog.h
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <dialogs/player-select-dialog.h>

#include <dialogs/entry-dialog.h>

#include <sudoku.h>
#include <config.h>

/**
 * @brief Construct a new PlayerSelectDialog.
 */
PlayerSelectDialog::PlayerSelectDialog(BaseObjectType *obj,
		Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app) :
		Gtk::Dialog(obj), app{app} {

	builder->get_widget("players-combo", players_combo);

	Gtk::Button *button;
	builder->get_widget("new-player-button", button);

	button->signal_clicked().connect([this]() { new_player_button_clicked(); });

	load_players();
}

/**
 * @brief Show the player dialog.
 * 
 * @param app Application context.
 * @return true if the dialog is accepted.
 */
bool PlayerSelectDialog::show(SudokuApp *app) {
	PlayerSelectDialog *dialog;
	auto builder = Gtk::Builder::create_from_file("../ui/player-select-dialog.glade");
	builder->get_widget_derived("player-select-dialog", dialog, app);

	auto result = dialog->run();
	dialog->close();

	if (result == Gtk::RESPONSE_ACCEPT) {
		// Save the current player configuration.
		app->save_board();
		app->get_player().save_config(app);

		// Load the new player.
		Config::set_current_player(dialog->players_combo->get_active_text());
		Config::save();
		app->get_board().set_id("");
		app->get_player().set_name(dialog->players_combo->get_active_text());
		app->get_player().load_config(app);

		app->load_board();

		return true;
	}

	return false;
}

/**
 * @brief Fills the combo with de current player list.
 * 
 */
void PlayerSelectDialog::load_players() {
	players_combo->remove_all();
	// Gets the player list
	for (auto p : Config::get_player_list()) {
		players_combo->append(p.get_name());
		if (app->get_player().get_name() == p.get_name()) {
			// Select the current player
			players_combo->set_active_text(p.get_name());
		}
	}

	this->show_all_children();
}

/**
 * @brief On new button click event.
 * 
 */
void PlayerSelectDialog::new_player_button_clicked() {
	const std::string name = EntryDialog::show("Enter the name of the new player:");
	
	if (name == "") return;

	// Check if player exists
	for (auto p : Config::get_player_list()) {
		if (p.get_name() == name) {
			auto parent = this;
			Gtk::MessageDialog dialog(*parent, "Player Exists", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, false);

			dialog.set_secondary_text("The player already exists.");
			dialog.run();
			return ;
		}
	}

	// Create the player
	Player new_player;
	new_player.new_player(name);

	load_players();
	
	// Select the new player on combo
	players_combo->set_active_text(name);
}
