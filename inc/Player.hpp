#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "GameMap.hpp"
# include "Utils.hpp"

class Player {
private:
	const GameMap& _GameMap;
	t_pos _playerPos;

public:
	Player(const GameMap& gameMap);
	~Player(void);

	const t_pos& getPosition(void) const;
	void move(double dx, double dy);
	void rotate(double angle);
} ;

#endif //PLAYER_HPP
