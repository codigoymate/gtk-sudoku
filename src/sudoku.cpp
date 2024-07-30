/**
 * @file sudoku.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of sudoku.h
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <sudoku.h>

#include <windows/main-window.h>
#include <windows/welcome-window.h>

#include <board.h>

#include <solver.h>
#include <generator.h>

#include <player.h>

#include <config.h>
#include <utils.h>

/**
 * @brief Construct a new SudokuApp object
 * 
 * @param argc 
 * @param argv 
 */
SudokuApp::SudokuApp(int argc, char *argv[]) :
		Gtk::Application(argc, argv, "com.codigoymate.sudoku") {
}

/**
 * @brief On game start.
 * 
 */
void SudokuApp::on_activate() {
	// CSS config
	auto css_provider = Gtk::CssProvider::create();
	css_provider->load_from_path("../ui/style.css");
	auto screen = Gdk::Screen::get_default();
	Gtk::StyleContext::add_provider_for_screen(screen, css_provider,
			GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	MainWindow *mw;
	auto builder = Gtk::Builder::create_from_file("../ui/main-window.glade");
	builder->get_widget_derived("main-window", mw, this);

	main_window = std::shared_ptr<MainWindow>(mw);
	this->add_window(*main_window);

	// Init configuration
	if (!Config::run_initials()) this->quit();

	// Load configuration
	if (!Config::load()) Config::save();
	Config::load();

	// Sets the player
	player.set_name(Config::get_current_player());
	//player.load_config();

	main_window->show_all();

	WelcomeWindow::show(this);
}

/**
 * @brief Start a new game.
 * @param difficulty game difficulty.
 */
void SudokuApp::new_game(const unsigned difficulty) {
	auto hiddens = 81;

	switch (difficulty) {
	// Easy
	case 0: hiddens -= Generator::rand_int(35, 45); break;
	// Medium
	case 1: hiddens -= Generator::rand_int(30, 34); break;
	// Hard
	case 2: hiddens -= Generator::rand_int(25, 29); break;
	}

	board = Generator::generate_board(hiddens, 1);

	auto sol = Solver::solve(board, 100);
	solved = sol.front();

	main_window->update();
}

int main(int argc, char *argv[]) {
	SudokuApp app(argc, argv);

	return app.run();
}
