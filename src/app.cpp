/**
 * @file app.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of app.h
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <app.h>

#include <main-window.h>
#include <sudoku.h>

/**
 * @brief Construct a new SudokuApp object
 * 
 * @param argc 
 * @param argv 
 */
SudokuApp::SudokuApp(int argc, char *argv[]) :
		Gtk::Application(argc, argv, "com.codigoymate.sudoku") {
	board = std::make_shared<Board>();
	board->load("../first-boards/1 sol 01.xml");
}

/**
 * @brief On game start.
 * 
 */
void SudokuApp::on_activate() {
	MainWindow *mw;
	auto builder = Gtk::Builder::create_from_file("../ui/main-window.glade");
	builder->get_widget_derived("main-window", mw, this);

	main_window = std::shared_ptr<MainWindow>(mw);
	this->add_window(*main_window);

	main_window->show_all();
}

int main(int argc, char *argv[]) {
	SudokuApp app(argc, argv);
	return app.run();
}
