#pragma once

#include <gtkmm.h>

class MainWindow;
class Board;

class SudokuApp: public Gtk::Application {
public:
	SudokuApp(int argc, char *argv[]);
	//virtual ~SudokuApp();

	std::shared_ptr<Board> getBoard() { return board; }

protected:
	void on_activate() override;

private:
	std::shared_ptr<MainWindow> main_window;
	std::shared_ptr<Board> board;
};
