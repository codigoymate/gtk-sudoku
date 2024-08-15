/**
 * @file welcome-window.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of welcome-window.h
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <windows/welcome-window.h>

#include <sudoku.h>
#include <windows/main-window.h>
#include <windows/collection-window.h>
#include <player.h>

#include <dialogs/new-game-dialog.h>
#include <dialogs/player-select-dialog.h>

/**
 * @brief Construct a new Welcome Window.
 * 
 * @param obj GObject instance.
 * @param builder Gtk::Builder reference.
 * @param app Pointer to the main application.
 */
WelcomeWindow::WelcomeWindow(BaseObjectType* obj,
		Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app) :
		Gtk::Window(obj), app{app} {

	builder->get_widget("welcome-label", welcome_label);

	Gtk::Button *button;

	builder->get_widget("switch-player-button", button);
	button->signal_clicked().connect([this]() {
		this->switch_player_button_clicked();
	});

	builder->get_widget("new-game-button", button);
	button->signal_clicked().connect([this]() {
		this->new_game_button_clicked();
	});

	builder->get_widget("collection-button", button);
	button->signal_clicked().connect([this]() {
		this->collection_button_clicked();
	});

	builder->get_widget("about-button", button);
	button->signal_clicked().connect([this]() {
		this->about_button_clicked();
	});

	builder->get_widget("exit-button", button);
	button->signal_clicked().connect([this]() {
		this->exit_button_clicked();
	});

	builder->get_widget("continue-button", continue_button);
	continue_button->signal_clicked().connect([this]() {
		this->continue_button_clicked();
	});

	signal_delete_event().connect([this](GdkEventAny *event) -> bool {
		return this->on_window_delete(event);
	});

	quit_app = true;

	update();
}

/**
 * @brief On close Welcome Window event. Quit the application
 * if simply close the windows.
 */
bool WelcomeWindow::on_window_delete(GdkEventAny* event) {

	if (quit_app) app->quit();

	return false;
}

/**
 * @brief Shows the welcome window.
 * 
 * @param app Application reference.
 */
void WelcomeWindow::show(SudokuApp *app) {
	WelcomeWindow *ww;
	auto builder = Gtk::Builder::create_from_file("../ui/welcome-window.glade");
	builder->get_widget_derived("welcome-window", ww, app);

	app->add_window(*ww);

	ww->set_transient_for(*app->get_main_window());

	ww->show_all();
}

/**
 * @brief Handles the click event for the switch player button.
 * 
 */
void WelcomeWindow::switch_player_button_clicked() {
	if (PlayerSelectDialog::show(app)) {
		update();
	}
}

/**
 * @brief Handles the click event for the new game button.
 * 
 */
void WelcomeWindow::new_game_button_clicked() {

	if (NewGameDialog::show(app)) {
		quit_app = false; // No exit
		this->close();
	}
}

/**
 * @brief Handles the click event for the continue button.
 * 
 */
void WelcomeWindow::continue_button_clicked() {

	quit_app = false; // No exit

	this->close();
	app->load_board();
	app->get_main_window()->update();
}

/**
 * @brief Handles the click event for the collection button.
 * 
 */
void WelcomeWindow::collection_button_clicked() {
	CollectionWindow::show(app, this);
}

/**
 * @brief Handles the click event for the about button.
 * 
 */
void WelcomeWindow::about_button_clicked() {
	app->show_about_dialog();
}

/**
 * @brief Handles the click event for the exit button.
 * 
 */
void WelcomeWindow::exit_button_clicked() {
	app->quit();
}

/**
 * @brief Refresh the window content with the config.
 * 
 */
void WelcomeWindow::update() {
	welcome_label->set_text("Welcome, " + app->get_player().get_name());
	continue_button->set_sensitive(app->get_board().get_id() != "");
}
