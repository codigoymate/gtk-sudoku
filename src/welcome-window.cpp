/**
 * @file welcome-window.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of welcome-window.h
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <welcome-window.h>

#include <sudoku.h>
#include <main-window.h>
#include <player.h>

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
	welcome_label->set_text("Welcome, " + app->get_player().get_name());

	Gtk::Button *button;
	builder->get_widget("new-game-button", button);
	button->signal_clicked().connect(sigc::mem_fun(
			*this, &WelcomeWindow::new_game_button_clicked));

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
 * @brief Handles the click event for the new game button.
 * 
 */
void WelcomeWindow::new_game_button_clicked() {
	app->new_game();
	this->close();
}
