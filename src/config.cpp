/**
 * @file config.cpp
 * @author Javier Candales (codigo.mate.9@gmail.com)
 * @brief Implementation of the Config class for Sudoku configuration management.
 * @date 2024-07-29
 * 
 */

#include <config.h>
#include <utils.h>
#include <player.h>
#include <libxml/parser.h>
#include <sys/types.h>
#include <assert.h>

/**
 * @brief Prepares the configuration.
 * 
 * This function checks if the home directory can be accessed and creates a directory
 * for the configuration if it doesn't exist.
 * 
 * @return false if the home directory cannot be found.
 */
const bool Config::run_initials() {
	char *home_path = std::getenv("HOME");
	if (home_path == nullptr) {
		std::cerr << "Could not find the home directory." << std::endl;
		return false;
	}

	config_path = std::string(home_path) + "/" + ".sudoku/";
	Utils::create_directory_if_not_exists(config_path);

	auto players = Config::get_player_list();

	if (players.empty()) {
		Player player;
		player.new_player(std::getenv("USER"));
	}

	return true;
}

/**
 * @brief Returns the list of players stored in the config directory.
 * 
 * This function reads the list of directories in the config path and creates a list
 * of Player objects from those directories.
 * 
 * @return A list of Player objects.
 */
std::list<Player> Config::get_player_list() {
	std::list<Player> list;
	auto dirs = Utils::get_dir_list(config_path);

	for (auto d : dirs) {
		Player p;
		p.set_name(d);
		list.push_back(p);
	}

	return list;
}

/**
 * @brief Loads the game configuration.
 * 
 * This function loads the configuration from the XML file in the config path. 
 * It sets the current player from the XML file or from the player list if the XML
 * does not contain a current player.
 * 
 * @return false if the configuration file cannot be read.
 */
const bool Config::load() {
	std::string config_file = config_path + "config.xml";

	auto doc = xmlReadFile(config_file.c_str(), "UTF-8", 0);
	if (!doc) return false;

	auto root_node = xmlDocGetRootElement(doc);

	current_player = std::string((char *)xmlGetProp(root_node, BAD_CAST "current-player"));

	if (current_player == "") {
		auto list = Config::get_player_list();
		if (list.empty()) std::cout << "Players not found." << std::endl;
		current_player = list.front().get_name();
		Config::save();
	}

	return true;
}

/**
 * @brief Saves the game configuration.
 * 
 * This function saves the current configuration to an XML file in the config path.
 * It ensures that the configuration directory exists and the XML file is saved correctly.
 */
void Config::save() {
	auto doc = xmlNewDoc(BAD_CAST "1.0");
	auto root_node = xmlNewNode(nullptr, BAD_CAST "sudoku-config");
	xmlDocSetRootElement(doc, root_node);

	xmlNewProp(root_node, BAD_CAST "current-player", BAD_CAST current_player.c_str());

	char *home_path = std::getenv("HOME");
	if (home_path == nullptr) {
		std::cerr << "Could not find the home directory." << std::endl;
		return;
	}

	std::string config_file = config_path + "config.xml";

	auto result = xmlSaveFormatFileEnc(config_file.c_str(), doc, "UTF-8", 1);
	assert(result != -1 && "Sudoku configuration: Cannot save xml file.");

	xmlFreeDoc(doc);
	xmlCleanupParser();
}

std::string Config::config_path = "";
std::string Config::current_player = "";
