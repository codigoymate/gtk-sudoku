#include <main-menu.h>

#include <app.h>

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

void MainMenu::menu_new_game() const {
	g_print("New Game !!\n");
}

void MainMenu::menu_quit() const {
	app->quit();
}
