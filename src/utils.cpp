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
