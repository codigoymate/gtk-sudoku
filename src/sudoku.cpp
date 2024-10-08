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

#include "version.h"

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

	css_provider->load_from_path(Utils::locate_ui("style.css"));
	
	auto screen = Gdk::Screen::get_default();
	Gtk::StyleContext::add_provider_for_screen(screen, css_provider,
			GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	MainWindow *mw;

	auto builder = Gtk::Builder::create_from_file(Utils::locate_ui("main-window.glade"));

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

	main_window->show_all();

	WelcomeWindow::show(this);
}

/**
 * @brief Start a new game.
 * @param size game type.
 * @param difficulty game difficulty.
 */
void SudokuApp::new_game(const unsigned size, const unsigned difficulty) {

	switch (difficulty) {
	// Easy
	case 0:
		if (size == 81)
			board = Generator::generate_board(Generator::rand_int(35, 45), 1, 81);
		else board = Generator::generate_board(Generator::rand_int(10, 11), 1, 16);
		board.set_difficulty("Easy");
		break;
	// Medium
	case 1:
		if (size == 81)
			board = Generator::generate_board(Generator::rand_int(30, 34), 1, 81);
		else board = Generator::generate_board(Generator::rand_int(8, 9), 1, 16);
		board.set_difficulty("Medium");
		break;
	// Hard
	case 2:
		if (size == 81)
			board = Generator::generate_board(Generator::rand_int(26, 29), 1, 81);
		else board = Generator::generate_board(Generator::rand_int(5, 7), 1, 16);
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
	if (board.empty()) return ;

	auto path = Config::get_config_path() + player.get_name() + "/collection/";
	Utils::create_directory_if_not_exists(path);
	board.save(path + board.get_id() + ".xml");
}

/**
 * @brief Load the current board from the player path.
 * 
 */
void SudokuApp::load_board() {

	// If no current board id.. no load. 
	if (board.get_id() == "") return;

	auto path = Config::get_config_path() + player.get_name() + "/collection/";
	board.load(path + board.get_id() + ".xml");
	
	auto solving = board;
	solving.reset();
	auto sol = Solver::solve(solving, 100);
	solved = sol.front();
}

/**
 * @brief Remove given board from collection.
 * 
 * @param board board to remove.
 */
void SudokuApp::remove_board(const Board &board) {
	// If the removing board is the current. Close it.
	if (board.get_id() == this->board.get_id()) {
		this->board = Board();
		this->solved = Board();
		main_window->update();

		player.save_config(this);
	}

	auto path = Config::get_config_path() + player.get_name() + "/collection/";
	path += board.get_id() + ".xml";

	Utils::remove_file(path);
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

	// sets the solved mark to show collection list.
	board.set_solved_mark(true);
	save_board();
}

/**
 * @brief Show the about Sudoku dialog.
 * 
 * @param parent the parent window.
 */
void SudokuApp::show_about_dialog() {
	Gtk::AboutDialog *dialog;
	auto builder = Gtk::Builder::create_from_file(Utils::locate_ui("about-dialog.glade"));
	builder->get_widget("about-dialog", dialog);

	dialog->set_version(SUDOKU_VERSION);

	auto response = dialog->run();
	if (response == Gtk::RESPONSE_CLOSE || response == Gtk::RESPONSE_DELETE_EVENT) {
		dialog->close();
	}
}

int main(int argc, char *argv[]) {
	SudokuApp app(argc, argv);

	return app.run();
	/*auto board = Generator::generate_board(30, 1, 81);
	board.print();
	std::cout << "Solutions " << Solver::solve(board, 100).size() << std::endl;*/
}
