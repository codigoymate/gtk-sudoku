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

/**
 * @brief Construct a new MainMenu object.
 */
MainMenu::MainMenu(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app) :
		Gtk::MenuBar(obj), app(app) {
	Gtk::MenuItem *item;

	builder->get_widget("new-game-menu-item", item);
	item->signal_activate().connect(sigc::mem_fun(
			*this, &MainMenu::menu_new_game));

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
 * @brief On Quit Game item click.
 * 
 */
void MainMenu::menu_quit() const {
	app->quit();
}
