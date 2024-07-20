/**
 * @file main-window.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Sudoku Gtk30 application window.
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <gtkmm.h>

class SudokuApp;
class MainMenu;
class BoardArea;

/**
 * @brief Main window class.
 * Contains main menu and Sudoku board.
 * 
 */
class MainWindow: public Gtk::ApplicationWindow {
public:
	/**
	 * @brief Construct a new Main Window object.
	 */
	MainWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder, SudokuApp *app);

private:
	SudokuApp *app; //* < Application instance.
	MainMenu *main_menu; //* < Main menu instance.
	BoardArea *board_area; //* < Board instance.
};
