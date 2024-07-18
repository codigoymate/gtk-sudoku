#pragma once

#include <gtkmm.h>

class SudokuApp;

class MainMenu: public Gtk::MenuBar {
public:
	MainMenu(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app);

private:

	void menu_new_game() const;
	void menu_quit() const;

	SudokuApp *app;
};
