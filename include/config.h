/**
 * @file config.h
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Configuration system for Sudoku.
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <iostream>
#include <list>

class Player;

/**
 * @brief Responsible for managing the configuration stored in
 * ~/.soduku.
 * 
 */
class Config {
public:
	/**
	 * @brief Prepares the configuration.

	 * @return false when the config directory cannot be created.
	 */
	static const bool run_initials();

	/**
	 * @brief Returns the list of players stored in the config directory.
	 */
	static std::list<Player> get_player_list();

	/**
	 * @brief Loads the game configuration.
	 * 
	 * @return false when the configuration could not be loaded.
	 */
	static const bool load();

	/**
	 * @brief Saves the game configuration.
	 * 
	 */
	static void save();

	/**
	 * @brief Returns the name of the current player.
	 * 
	 * @return const std::string name of the current player.
	 */
	static const std::string get_current_player() { return current_player; }

	/**
	 * @brief Sets the name of the current player.
	 * 
	 * @param player name of the current player.
	 */
	static void set_current_player(const std::string player) { current_player = player; }

	/**
	 * @brief Get the config path from home
	 * 
	 * @return const std::string 
	 */
	static const std::string get_config_path() { return config_path; }

private:
	static std::string config_path; /**< Path to the configuration directory */
	static std::string current_player; /**< Name of the current player */
};
