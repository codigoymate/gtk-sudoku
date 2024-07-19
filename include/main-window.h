#pragma once

#include <gtkmm.h>

class SudokuApp;
class MainMenu;
class BoardArea;

class MainWindow: public Gtk::ApplicationWindow {
public:
	MainWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app);

private:
	SudokuApp *app;
	MainMenu *main_menu;
	BoardArea *board_area;
};
