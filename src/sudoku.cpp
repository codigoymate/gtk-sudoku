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
	player.load_config(this);

	/*if (board.get_id() != "")
		this->load_board();*/

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
	case 0:
		board = Generator::generate_board(81 - Generator::rand_int(35, 45), 1);
		board.set_difficulty("Easy");
		break;
	// Medium
	case 1:
		board = Generator::generate_board(81 - Generator::rand_int(30, 34), 1);
		board.set_difficulty("Medium");
		break;
	// Hard
	case 2:
		board = Generator::generate_board(81 - Generator::rand_int(25, 29), 1);
		board.set_difficulty("Hard");
		break;
	}

	auto sol = Solver::solve(board, 100);
	solved = sol.front();

	this->save_board();
	player.save_config(this);

	main_window->update();
}

/**
 * @brief Save the current board to the player path.
 * 
 */
void SudokuApp::save_board() {
	auto path = Config::get_config_path() + player.get_name() + "/collection/";
	Utils::create_directory_if_not_exists(path);
	board.save(path + board.get_id() + ".xml");
}

/**
 * @brief Load the current board from the player path.
 * 
 */
void SudokuApp::load_board() {
	auto path = Config::get_config_path() + player.get_name() + "/collection/";
	board.load(path + board.get_id() + ".xml");
	
	auto solving = board;
	solving.reset();
	auto sol = Solver::solve(solving, 100);
	solved = sol.front();
}

/**
 * @brief This is called when the player completes the game.
 * 
 */
void SudokuApp::player_wins() {
	auto parent = std::static_pointer_cast<Gtk::Window>(main_window);
	Gtk::MessageDialog dialog(*parent, "Success", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, false);

	dialog.set_secondary_text("Solved !");
	dialog.run();

	save_board();
}

int main(int argc, char *argv[]) {
	SudokuApp app(argc, argv);

	return app.run();
}
