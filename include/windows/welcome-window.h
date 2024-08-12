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
	 * @brief On close Welcome Window event. Quit the application
	 * if simply close the windows.
	 */
	bool on_window_delete(GdkEventAny* event);

	/**
	 * @brief Shows the welcome window.
	 * 
	 * @param app Application reference.
	 */
	static void show(SudokuApp *app);

	/**
	 * @brief Set the true if closed WelcomeWindow, quit application.
	 */
	void set_quit_app(const bool quit_app) { this->quit_app = quit_app; }

private:

	/**
	 * @brief Handles the click event for the switch player button.
	 * 
	 */
	void switch_player_button_clicked();

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

	/**
	 * @brief Handles the click event for the collection button.
	 * 
	 */
	void collection_button_clicked();

	/**
	 * @brief Handles the click event for the about button.
	 * 
	 */
	void about_button_clicked();

	/**
	 * @brief Handles the click event for the exit button.
	 * 
	 */
	void exit_button_clicked();

	/**
	 * @brief Refresh the window content with the config.
	 * 
	 */
	void update();

	SudokuApp *app; /**< Main application */
	Gtk::Label *welcome_label; /**< Welcome message label */
	Gtk::Button *continue_button;

	bool quit_app{};
};
