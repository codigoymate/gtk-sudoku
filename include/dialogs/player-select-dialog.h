/**
 * @file player-select-dialog.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Dialog to switch a sudoku player.
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <gtkmm.h>

#include <sudoku.h>

/**
 * @brief Dialog to switch a sudoku player. Manage config to switch and
 * create a new player.
 * 
 */
class PlayerSelectDialog: public Gtk::Dialog {
public:
	/**
	 * @brief Construct a new PlayerSelectDialog.
	 */
	PlayerSelectDialog(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app);

	/**
	 * @brief Show the player dialog.
	 * 
	 * @param app Application context.
	 * @return true if the dialog is accepted.
	 */
	static bool show(SudokuApp *app);

private:
	/**
	 * @brief Fills the combo with de current player list.
	 * 
	 */
	void load_players();

	/**
	 * @brief On new button click event.
	 * 
	 */
	void new_player_button_clicked();

	/**
	 * @brief On remove button click event.
	 * 
	 */
	void remove_player_button_clicked();

	/**
	 * @brief On rename button click event.
	 * 
	 */
	void rename_player_button_clicked();

	SudokuApp *app; /**< Sudoku application */
	Gtk::ComboBoxText *players_combo;
};
