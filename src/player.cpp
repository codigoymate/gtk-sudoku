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

#include <utils.h>

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

	player_path += "/" + name;
	Utils::create_directory_if_not_exists(player_path);

	
}

