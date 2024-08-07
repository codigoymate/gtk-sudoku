/**
 * @file utils.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Utility functions for file and directory operations.
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <iostream>
#include <list>

#include <cairomm/context.h>

#include <board.h>

class Utils {
public:
	/**
	 * @brief Creates a directory if it does not exist.
	 * 
	 * This function checks if the specified directory exists, and if not, it creates it.
	 * 
	 * @param path The path of the directory to create.
	 */
	static void create_directory_if_not_exists(const std::string path);

	/**
	 * @brief Gets a list of directories in the specified path.
	 * 
	 * This function retrieves the names of all directories within the specified path.
	 * 
	 * @param path The path to search for directories.
	 * @return A list of directory names.
	 */
	static std::list<std::string> get_dir_list(const std::string path);

	/**
	 * @brief Gets a list of files in the specified path.
	 * 
	 * This function retrieves the names of all files within the specified path.
	 * 
	 * @param path The path to search for files.
	 * @return A list of filenames.
	 */
	static std::list<std::string> get_file_list(const std::string path);

	/**
	 * @brief Draw Sudoku grid on cairo context.
	 * 
	 * @param cr Cairo context.
	 * @param w width of the widget.
	 * @param h height of the widget.
	 */
	static void draw_grid(const Cairo::RefPtr<Cairo::Context>& cr, const Board &board,
		const unsigned w, const unsigned h,
		const int sel_x, const int sel_y,
		const bool error);
};
