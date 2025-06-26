#ifndef GAME_HPP
#define GAME_HPP

# define SCREEN_WIDTH 1024u
# define SCREEN_HEIGHT 768u

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include "../inc/GameMap.hpp"
# include "../inc/Player.hpp"
# include <iostream>

typedef struct s_rc_params {
	double 	cameraX;
	double 	rayDirX;
	double 	rayDirY;
	int 	mapX;
	int 	mapY;
	double 	deltaDistX;
	double 	deltaDistY;
	int 	stepX;
	int 	stepY;
	int 	side;
	double 	sideDistX;
	double	sideDistY;
	int		lineHeight;
	int		drawStart;
	double 	perpWallDist;
} t_rc_params;

sf::RenderWindow 	window_setup(void);
void 				raycast(Player& player, const GameMap& gameMap,
			 			sf::RenderWindow& window);
void				game_loop(std::string& map_path);

#endif //GAME_HPP
