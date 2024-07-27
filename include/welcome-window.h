#pragma once

#include <gtkmm.h>

class SudokuApp;

class WelcomeWindow: public Gtk::Window {
public:
	WelcomeWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app);

	static void show(SudokuApp *app);
private:

	void new_game_button_clicked();

	SudokuApp *app;
};
