/**
 * @file player.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of player.h
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <player.h>

#include <iostream>
#include <sys/stat.h>

/**
 * @brief Create a new player.
 * Create and store the player information in home directory.
 * 
 * @param name the player name.
 */
void Player::new_player(const std::string name) {
	set_name(name);
	char *home_path = std::getenv("HOME");
	if (home_path == nullptr) {
		std::cerr << "Could not find the home directory." << std::endl;
		return;
	}

	auto player_path = std::string(home_path) + "/" + ".sudoku";
	create_directory_if_not_exists(player_path);

	player_path += "/" + name;
	create_directory_if_not_exists(player_path);

	
}

void Player::create_directory_if_not_exists(const std::string path) {
	struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        mkdir(path.c_str(), 0775); // Cannot access path
    } else if (info.st_mode & S_IFDIR) {
        return ; // Path is a directory
    } else {
        mkdir(path.c_str(), 0775); // Path is not a directory
    }
}
