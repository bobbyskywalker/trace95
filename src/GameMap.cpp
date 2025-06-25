#include "../inc/GameMap.hpp"

GameMap::GameMap(const std::string& map_filepath) : _mapFilepath(map_filepath) { _loadMapFile(); }

GameMap::~GameMap(void) {}

const std::vector<std::string>& GameMap::getMap(void) const {
	return (_2dMap);
}

const std::string& GameMap::getTexturePath(char id) const {
	switch (id) {
		case 'N': return (_NTexturePath);
		case 'S': return (_STexturePath);
		case 'W': return (_WTexturePath);
		case 'E': return (_ETexturePath);
		default:
			static const std::string empty = "";
		return (empty);
	}
}

const sf::Texture& GameMap::getTexture(char side) const {
	switch (side) {
		case 'N': return (_textureNorth);
		case 'S': return (_textureSouth);
		case 'W': return (_textureWest);
		case 'E': return (_textureEast);
		default:
			throw std::runtime_error("Invalid wall side: " + std::string(1, side));
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