/**
 * @file main-window.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of main-window.h
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <windows/main-window.h>

#include <main-menu.h>
#include <board-area.h>
#include <sudoku.h>

/**
 * @brief Construct a new Main Window:: Main Window object.
 */
MainWindow::MainWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app) :
		Gtk::ApplicationWindow(obj), app(app) {
	builder->get_widget_derived("main-menu", main_menu, app);
	builder->get_widget_derived("board-area", board_area, app);

	builder->get_widget("board-name-label", board_name_label);
	builder->get_widget("level-label", level_label);
	builder->get_widget("number-box", number_box);

	signal_delete_event().connect(sigc::mem_fun(*this, &MainWindow::on_window_delete));
}

/**
 * @brief On Main Window close event. Save the configuration.
 */
bool MainWindow::on_window_delete(GdkEventAny* event) {
	// No save if the board is empty
	if (!app->get_board().empty())
		app->save_board();
		app->get_player().save_config(app);

	return false;
}

/**
 * @brief Update the information labels of main windows.
 * 
 */
void MainWindow::update() {
	board_name_label->set_text("Game: " + app->get_board().get_name());
	level_label->set_text("Level: " + app->get_board().get_difficulty());
	board_area->queue_draw();

	// Update number buttons
	for (auto *child : number_box->get_children()) number_box->remove(*child);
	for (unsigned i = 0; i < unsigned(std::sqrt(app->get_board().get_size())); i ++) {
		auto button = Gtk::make_managed<Gtk::Button>(std::to_string(i + 1));
		button->set_can_focus(false);

		button->signal_clicked().connect([this, button]() {
			app->get_main_window()->get_board_area()->chosen_a_number(
				button->get_label().c_str()[0] - '0'
			);
		});

		number_box->add(*button);
	}

	number_box->show_all();
}

