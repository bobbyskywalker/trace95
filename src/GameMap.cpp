#include "../inc/GameMap.hpp"

GameMap::GameMap(const std::string& map_filepath) : _mapFilepath(map_filepath) { _loadMapFile(); }

GameMap::~GameMap(void) {}

const std::vector<std::string>& GameMap::getMap(void) const {
	return (_2dMap);
}

const std::string& GameMap::getTexture(char id) const {
	switch (id) {
		case 'N': return (_NTexture);
		case 'S': return (_STexture);
		case 'W': return (_WTexture);
		case 'E': return (_ETexture);
		default:
			static const std::string empty = "";
		return (empty);
	}
}

const sf::Color GameMap::getFloorColor(void) const {
	return (_floorColor);
}

const sf::Color GameMap::getCeilColor(void) const {
	return (_ceilColor);
}

const t_pos& GameMap::getPlayerStartPos(void) const {
	return (_playerStartPos);
}