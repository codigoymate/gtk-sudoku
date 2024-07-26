/**
 * @file player.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief User name module to store a session.
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <string>

/**
 * @brief Represents a player.
 * 
 */
class Player {
public:
	/**
	 * @brief Construct a new Player object
	 * 
	 */
	Player() = default;

	/**
	 * @brief Set the player name.
	 */
	void set_name(const std::string name) { this->name = name; }

	/**
	 * @brief Get the player name.
	 * 
	 * @return const std::string 
	 */
	const std::string get_name() const { return name; }

	/**
	 * @brief Create a new player.
	 * Create and store the player information in home directory.
	 * 
	 * @param name the player name.
	 */
	void new_player(const std::string name);

private:
	std::string name; /** < Player name */

	void create_directory_if_not_exists(const std::string path);
};
