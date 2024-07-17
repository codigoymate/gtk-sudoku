#pragma once

#include <gtkmm.h>

class MainWindow;

class SudokuApp: public Gtk::Application {
public:
	SudokuApp(int argc, char *argv[]);
	//virtual ~SudokuApp();

protected:
	void on_activate() override;

private:
	std::shared_ptr<MainWindow> main_window;
};
