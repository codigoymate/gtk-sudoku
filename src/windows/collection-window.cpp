/**
 * @file collection-window.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of collection-window.h
 * @date 2024-08-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <windows/collection-window.h>

#include <windows/main-window.h>
#include <windows/welcome-window.h>

#include <sudoku.h>
#include <board.h>
#include <config.h>
#include <utils.h>

#include <board-view.h>

/**
 * @brief Construct a new CollectionWindow
 */
CollectionWindow::CollectionWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder,
			SudokuApp *app, WelcomeWindow *ww) : Gtk::Window(obj), app{app}, welcomeWindow{ww} {
	builder->get_widget("board-flow", board_flow);
	board_flow->signal_selected_children_changed().connect([this]() {
		this->board_flow_selection_changed();
	});

	builder->get_widget("play-button", play_button);
	play_button->signal_clicked().connect([this]() {
		this->play_button_clicked();
	});

	builder->get_widget("remove-button", remove_button);
	remove_button->signal_clicked().connect([this]() {
		this->remove_button_clicked();
	});

	load_boards();

	update();
}

/**
 * @brief Show this window.
 * 
 * @param app Application context.
 * @param parent Parent window.
 */
void CollectionWindow::show(SudokuApp *app, WelcomeWindow *ww) {
	CollectionWindow *cw;
	auto builder = Gtk::Builder::create_from_file("../ui/collection-window.glade");
	builder->get_widget_derived("collection-window", cw, app, ww);

	app->add_window(*cw);

	cw->set_transient_for(*ww);

	cw->show_all();
}

/**
 * @brief Load board list from collection and fills list flow.
 * 
 */
void CollectionWindow::load_boards() {
	board_list.clear();
	for (auto *child : board_flow->get_children()) board_flow->remove(*child);

	auto file_list = Utils::get_file_list(Config::get_config_path() + 
						Config::get_current_player() + "/collection");
	for (auto file : file_list) {
		Board board;
		board.load(Config::get_config_path() + Config::get_current_player() + 
				"/collection/" + file);
		board_list.push_back(board);
	}

	this->sort_boards();

	for (auto &board : board_list) {
		auto vbox = Gtk::make_managed<Gtk::Box>();
		vbox->set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
		board_flow->add(*vbox);

		// Board view
		auto board_view = Gtk::make_managed<BoardView>(board);
		board_view->set_size_request(150, 150);
		board_view->set_halign(Gtk::Align::ALIGN_CENTER);
		vbox->add(*board_view);

		// Board name
		auto name_label = Gtk::make_managed<Gtk::Label>(board.get_name());
		name_label->get_style_context()->add_class("board-name");
		vbox->add(*name_label);

		auto hbox = Gtk::make_managed<Gtk::Box>();
		hbox->set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
		hbox->set_halign(Gtk::Align::ALIGN_CENTER);
		hbox->set_spacing(7);
		vbox->add(*hbox);

		// Difficulty
		hbox->add(*Gtk::make_managed<Gtk::Label>(board.get_difficulty()));

		// Solved
		if (board.is_solved_mark()) {

			// Add a separator
			hbox->add(*Gtk::make_managed<Gtk::Separator>());

			// Solved label
			auto solved = Gtk::make_managed<Gtk::Label>("Solved");
			solved->get_style_context()->add_class("solved-board-name");
			hbox->add(*solved);
		}
	}

	board_flow->show_all();
}

/**
 * @brief Sort the board list from most recent to old.
 * 
 */
void CollectionWindow::sort_boards() {
	for (signed i = 0; i < board_list.size() - 1; i ++) {
		if (board_list[i].get_id() > board_list[i + 1].get_id()) {
			auto tmp = board_list[i];
			board_list[i] = board_list[i + 1];
			board_list[i + 1] = tmp;
			i = -1;
		}
	}
}

/**
 * @brief Selection change event
 * 
 */
void CollectionWindow::board_flow_selection_changed() {
	update();
}

/**
 * @brief Play button clicked event.
 * 
 */
void CollectionWindow::play_button_clicked() {

	unsigned index = 0;

	for (auto item : board_flow->get_children()) {
		if (item == board_flow->get_selected_children().front()) {
			break;
		} index ++;
	}

	welcomeWindow->set_quit_app(false);
	this->close();
	welcomeWindow->close();
	app->get_board().set_id(board_list[index].get_id());
	app->get_player().save_config(app);
	app->load_board();
	app->get_main_window()->update();
}

/**
 * @brief Remove button clicked event.
 * 
 */
void CollectionWindow::remove_button_clicked() {
	unsigned index = 0;

	for (auto item : board_flow->get_children()) {
		if (item == board_flow->get_selected_children().front()) {
			break;
		} index ++;
	}

	Gtk::MessageDialog dialog(*app->get_main_window(), "Remove game?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
	dialog.set_secondary_text("Remove the game permanently from the collection.");

	int result = dialog.run();
	if (result == Gtk::RESPONSE_NO) return;

	app->remove_board(board_list[index]);

	load_boards();
	update();

	welcomeWindow->update();
}

/**
 * @brief Update some controls of the window.
 * 
 */
void CollectionWindow::update() {
	if (board_flow->get_selected_children().size() == 0) {
		play_button->set_sensitive(false);
		remove_button->set_sensitive(false);
	} else {
		play_button->set_sensitive(true);
		remove_button->set_sensitive(true);
	}
}
