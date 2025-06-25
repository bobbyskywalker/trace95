#include "../inc/Player.hpp"

Player::Player(const GameMap& gameMap) : _GameMap(gameMap) {
	_playerPos = gameMap.getPlayerStartPos();
}

Player::~Player(void) {}