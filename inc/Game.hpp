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


/* SECTION: window/SFML setup */
sf::RenderWindow 	window_setup(void);

/* SECTION: raycasting utils */
void 				compute_raydir(t_rc_params& rc_params, unsigned int x, t_pos& p);
void 				init_dda(t_rc_params& rc_params, t_pos& p);
void 				perform_dda(t_rc_params& rc_params, const std::vector<std::string> & map);
void 				calc_wall_projection(t_rc_params& rc_params);
void 				apply_wall_textures(t_rc_params& rc_params, const GameMap& gameMap, t_pos& p,
								unsigned int x, sf::RenderWindow& window);
void 				apply_floor_ceil_colors(const GameMap& gameMap, sf::RenderWindow& window);
void 				draw_crosshair(sf::RenderWindow& window);

/* SECTION: raycast core */
void 				raycast(Player& player, const GameMap& gameMap,
			 			sf::RenderWindow& window);

/* SECTION: game loop core */
void				game_loop(std::string& map_path);

#endif //GAME_HPP
