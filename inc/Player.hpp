#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "GameMap.hpp"
# include "Utils.hpp"
# include <math.h>

class Player {
private:
	const GameMap& _GameMap;
	t_pos _playerPos;
	double _time;
	double _oldTime;

public:
	Player(const GameMap& gameMap);
	~Player(void);

	const t_pos& getPosition(void) const;

	void moveForward(float speed, const GameMap& map);
	void moveBackward(float speed, const GameMap& map);
	void strafeLeft(float speed, const GameMap& map);
	void strafeRight(float speed, const GameMap& map);
	void rotate(double angle);
} ;

#endif //PLAYER_HPP
