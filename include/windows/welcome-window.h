/**
 * @file welcome-window.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief GTK3 Welcome window for Sudoku game.
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <gtkmm.h>

class SudokuApp;

/**
 * @brief Represents the welcome window.
 * 
 */
class WelcomeWindow : public Gtk::Window {
public:
	/**
	 * @brief Construct a new Welcome Window.
	 * 
	 * @param obj GObject instance.
	 * @param builder Gtk::Builder reference.
	 * @param app Pointer to the main application.
	 */
	WelcomeWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app);

	/**
	 * @brief Shows the welcome window.
	 * 
	 * @param app Application reference.
	 */
	static void show(SudokuApp *app);

private:
	/**
	 * @brief Handles the click event for the new game button.
	 * 
	 */
	void new_game_button_clicked();

	/**
	 * @brief Handles the click event for the continue button.
	 * 
	 */
	void continue_button_clicked();

	SudokuApp *app; /**< Main application */
	Gtk::Label *welcome_label; /**< Welcome message label */
};