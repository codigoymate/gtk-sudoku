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
#include <config.h>
#include <sudoku.h>

#include <libxml/parser.h>
#include <assert.h>

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

/**
 * @brief Remove player from disk.
 * 
 */
void Player::remove_player() {
	char *home_path = std::getenv("HOME");
	if (home_path == nullptr) {
		std::cerr << "Could not find the home directory." << std::endl;
		return;
	}

	auto player_path = std::string(home_path) + "/" + ".sudoku";

	player_path += "/" + name;

	std::cout << "Removing directory: " << player_path << "." << std::endl;
	Utils::remove_directory(player_path);
}

/**
 * @brief Save the player configuration.
 * 
 */
void Player::save_config(SudokuApp *app) const {
	
	auto doc = xmlNewDoc(BAD_CAST "1.0");
	auto root_node = xmlNewNode(nullptr, BAD_CAST "sudoku-config");
	xmlDocSetRootElement(doc, root_node);

	std::string cboard = "";
	// Remove current board from configuration if board is empty.
	if (!app->get_board().empty())
		cboard = app->get_board().get_id();

	xmlNewProp(root_node, BAD_CAST "current-board", BAD_CAST cboard.c_str());

	auto path = Config::get_config_path() + name + "/config.xml";

	std::cout << "Saving player config: " << path << "." << std::endl;

	auto result = xmlSaveFormatFileEnc(path.c_str(), doc, "UTF-8", 1);
	assert(result != -1 && "Sudoku configuration: Cannot save xml file.");

	xmlFreeDoc(doc);
	xmlCleanupParser();
}

/**
 * @brief Load the player configuration.
 * 
 * @return false if cannot load the config file.
 */
const bool Player::load_config(SudokuApp *app) {
	auto path = Config::get_config_path() + name + "/config.xml";

	std::cout << "Loading player config: " << path << "." << std::endl;

	app->get_board().set_id("");

	auto doc = xmlReadFile(path.c_str(), "UTF-8", 0);
	if (!doc) {
		std::cout << "[!]Cannot load config player: " << path << "." << std::endl;
		return false;
	}

	auto root_node = xmlDocGetRootElement(doc);

	app->get_board().set_id(
		std::string((char *)xmlGetProp(root_node, BAD_CAST "current-board"))
	);

	return true;
}

