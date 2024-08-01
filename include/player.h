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

class SudokuApp;

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

	/**
	 * @brief Save the player configuration.
	 * 
	 */
	void save_config(SudokuApp *app) const;

	/**
	 * @brief Load the player configuration.
	 * 
	 * @return false if cannot load the config file.
	 */
	const bool load_config(SudokuApp *app);

private:
	std::string name; /** < Player name */
};
