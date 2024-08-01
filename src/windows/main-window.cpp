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
}

/**
 * @brief Update the information labels of main windows.
 * 
 */
void MainWindow::update() {
	board_name_label->set_text("Game: " + app->get_board().get_name());
	level_label->set_text("Level: " + app->get_board().get_difficulty());
	board_area->queue_draw();
}
