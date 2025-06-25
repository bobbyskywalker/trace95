#include "../inc/Player.hpp"

Player::Player(const GameMap& gameMap) : _GameMap(gameMap) {
	_playerPos = gameMap.getPlayerStartPos();
	_time = 0;
	_oldTime = 0;
}

Player::~Player(void) {}

const t_pos& Player::getPosition(void) const {
	return (_playerPos);
}

void Player::moveForward(float speed, const GameMap& map) {
	auto m = map.getMap();
	double newX = _playerPos.posX + _playerPos.dirX * speed;
	double newY = _playerPos.posY + _playerPos.dirY * speed;

	if (m[static_cast<int>(_playerPos.posY)][static_cast<int>(newX)] == '0')
		_playerPos.posX = newX;
	if (m[static_cast<int>(newY)][static_cast<int>(_playerPos.posX)] == '0')
		_playerPos.posY = newY;
}

void Player::moveBackward(float speed, const GameMap& map) {
	auto m = map.getMap();
	double newX = _playerPos.posX - _playerPos.dirX * speed;
	double newY = _playerPos.posY - _playerPos.dirY * speed;

	if (m[static_cast<int>(_playerPos.posY)][static_cast<int>(newX)] == '0')
		_playerPos.posX = newX;
	if (m[static_cast<int>(newY)][static_cast<int>(_playerPos.posX)] == '0')
		_playerPos.posY = newY;
}


void Player::strafeLeft(float speed, const GameMap& map) {
	auto m = map.getMap();
	double strafeX = _playerPos.dirY;
	double strafeY = -_playerPos.dirX;
	int x = static_cast<int>(_playerPos.posX + strafeX * speed);
	int y = static_cast<int>(_playerPos.posY + strafeY * speed);
	if (m[y][x] == '0') _playerPos.posX += strafeX * speed;
	if (m[y][x] == '0') _playerPos.posY += strafeY * speed;
}

void Player::strafeRight(float speed, const GameMap& map) {
	auto m = map.getMap();
	double strafeX = -_playerPos.dirY;
	double strafeY = _playerPos.dirX;
	int x = static_cast<int>(_playerPos.posX + strafeX * speed);
	int y = static_cast<int>(_playerPos.posY + strafeY * speed);
	if (m[y][x] == '0') _playerPos.posX += strafeX * speed;
	if (m[y][x] == '0') _playerPos.posY += strafeY * speed;
}

void Player::rotate(double angle) {
	float oldDirX = _playerPos.dirX;
	_playerPos.dirX = _playerPos.dirX * cos(angle) - _playerPos.dirY * sin(angle);
	_playerPos.dirY = oldDirX * sin(angle) + _playerPos.dirY * cos(angle);

	float oldPlaneX = _playerPos.planeX;
	_playerPos.planeX = _playerPos.planeX * cos(angle) - _playerPos.planeY * sin(angle);
	_playerPos.planeY = oldPlaneX * sin(angle) + _playerPos.planeY * cos(angle);
}