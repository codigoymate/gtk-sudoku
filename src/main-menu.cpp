/**
 * @file main-menu.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of main-menu.h
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <main-menu.h>

#include <app.h>
#include <main-window.h>
#include <board-area.h>
#include <sudoku.h>

/**
 * @brief Construct a new MainMenu object.
 */
MainMenu::MainMenu(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app) :
		Gtk::MenuBar(obj), app(app) {
	Gtk::MenuItem *item;

	builder->get_widget("new-game-menu-item", item);
	item->signal_activate().connect(sigc::mem_fun(
			*this, &MainMenu::menu_new_game));

	builder->get_widget("check-board-menu-item", item);
	item->signal_activate().connect(sigc::mem_fun(
			*this, &MainMenu::menu_check_board));

	builder->get_widget("quit-menu-item", item);
	item->signal_activate().connect(sigc::mem_fun(
			*this, &MainMenu::menu_quit));
}

/**
 * @brief On New Game item click.
 * 
 */
void MainMenu::menu_new_game() const {
	g_print("New Game !!\n");
}

/**
 * @brief On Check board item click;
 * 
 */
void MainMenu::menu_check_board() const {

	auto parent = std::static_pointer_cast<Gtk::Window>(app->get_main_window());
	Gtk::MessageDialog dialog(*parent, "Checking Game", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false);

	auto actual = app->get_board();
	auto solved = app->get_solved();

	for (unsigned y = 0; y < 9; y ++) {
		for (unsigned x = 0; x < 9; x ++) {
			if (actual.get(x, y).value == 0) continue;
			if (actual.get(x, y).value == solved.get(x, y).value) continue;

			// Error found
			app->get_main_window()->get_board_area()->select(x, y, true);

			dialog.set_secondary_text("Error found !.");
			dialog.run();

			return ;
		}
	}

	dialog.set_secondary_text("No errors so far.");
	dialog.run();

}

/**
 * @brief On Quit Game item click.
 * 
 */
void MainMenu::menu_quit() const {
	app->quit();
}
