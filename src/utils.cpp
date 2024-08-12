/**
 * @file utils.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of utils.h
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <utils.h>

#include <sys/stat.h>
#include <dirent.h>
#include <cstring>

/**
 * @brief Creates a directory if it does not exist.
 * 
 * This function checks if the specified directory exists, and if not, it creates it.
 * 
 * @param path The path of the directory to create.
 */
void Utils::create_directory_if_not_exists(const std::string path) {
	struct stat info;
	if (stat(path.c_str(), &info) != 0) {
		std::cout << "Creating directory: " << path << "." << std::endl;
		mkdir(path.c_str(), 0775); // Cannot access path
	} else if (info.st_mode & S_IFDIR) {
		return ; // Path is a directory
	} else {
		std::cout << "Creating directory: " << path << "." << std::endl;
		mkdir(path.c_str(), 0775); // Path is not a directory
	}
}

/**
 * @brief Gets a list of directories in the specified path.
 * 
 * This function retrieves the names of all directories within the specified path.
 * 
 * @param path The path to search for directories.
 * @return A list of directory names.
 */
std::list<std::string> Utils::get_dir_list(const std::string path) {
	
	std::list<std::string> result;

	DIR* dir = opendir(path.c_str());
	if (dir == nullptr) {
		std::cerr << "Error: cannot open directory: " << path << std::endl;
		return result;
	}

	struct dirent* entry;
	struct stat info;

	while ((entry = readdir(dir)) != nullptr) {
		std::string full_path = std::string(path) + "/" + entry->d_name;
		if (stat(full_path.c_str(), &info) != 0) {
			std::cerr << "Error: obtaining info from " << full_path << std::endl;
			continue;
		}
		if (S_ISDIR(info.st_mode)) {
			// ignore "." y ".."
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
				result.push_back(entry->d_name);
			}
		}
	}

	closedir(dir);

	return result;
}

/**
 * @brief Gets a list of files in the specified path.
 * 
 * This function retrieves the names of all files within the specified path.
 * 
 * @param path The path to search for files.
 * @return A list of filenames.
 */
std::list<std::string> Utils::get_file_list(const std::string path) {
	std::list<std::string> result;

	DIR* dir = opendir(path.c_str());
	if (dir == nullptr) {
		std::cerr << "Error: cannot open directory: " << path << std::endl;
		return result;
	}

	struct dirent* entry;
	struct stat info;

	while ((entry = readdir(dir)) != nullptr) {
		std::string full_path = std::string(path) + "/" + entry->d_name;
		if (stat(full_path.c_str(), &info) != 0) {
			std::cerr << "Error: obtaining info from " << full_path << std::endl;
			continue;
		}
		if (S_ISDIR(info.st_mode)) continue;
		else result.push_back(entry->d_name);
	}

	closedir(dir);

	return result;
}

/**
 * @brief Draw Sudoku grid on cairo context.
 * 
 * @param cr Cairo context.
 * @param w width of the widget.
 * @param h height of the widget.
 */
void Utils::draw_grid(const Cairo::RefPtr<Cairo::Context>& cr, const Board &board,
		const unsigned w, const unsigned h,
		const int sel_x, const int sel_y,
		const bool error) {

	double s_size = double(w <= h ? w : h) / (board.get_size() == 81 ? 9.0 : 4.0);

	auto s = board.get_size() == 81 ? 9 : 4;

	for (unsigned y = 0; y < s; y ++) {
		for (unsigned x = 0; x < s; x ++) {

			// Draw Rectangle
			if (board.get(x, y).fixed) cr->set_source_rgb(0.8, 0.8, 0.8);
			else cr->set_source_rgb(1, 1, 1);

			if (x == sel_x && y == sel_y) {
				if (!board.get(x, y).fixed) {
					if (error) {
						cr->set_source_rgb(1.0, 0.6, 0.6);
						//error = false;
					}
					else cr->set_source_rgb(0.7, 1.0, 0.7);
				}
			}
			
			cr->rectangle(x * s_size, y * s_size, s_size, s_size);
			cr->fill();

			cr->set_source_rgb(0, 0, 0);
			cr->set_line_width(s_size * 0.02);
			cr->rectangle(x * s_size, y * s_size, s_size, s_size);

			cr->stroke();

			// Draw number
			if (board.get(x, y).value) {
				cr->select_font_face("sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD);
				cr->set_font_size(s_size * 0.7);
				cr->move_to(x * s_size + s_size * 0.25, y * s_size + s_size * 0.8);
				cr->show_text(std::to_string(board.get(x, y).value));
			}
		}
	}

	// Draw Separators
	cr->set_source_rgb(0, 0, 0);
	cr->set_line_width(s_size * 0.09);

	if (board.get_size() == 81) {
		cr->move_to(s_size * 3, 0);
		cr->line_to(s_size * 3, s_size * 9);
		cr->move_to(s_size * 6, 0);
		cr->line_to(s_size * 6, s_size * 9);

		cr->move_to(0, s_size * 3);
		cr->line_to(s_size * 9, s_size * 3);
		cr->move_to(0, s_size * 6);
		cr->line_to(s_size * 9, s_size * 6);
	} else {
		cr->move_to(s_size * 2, 0);
		cr->line_to(s_size * 2, s_size * 4);
		cr->move_to(0, s_size * 2);
		cr->line_to(s_size * 4, s_size * 2);
	}

	cr->stroke();

}
