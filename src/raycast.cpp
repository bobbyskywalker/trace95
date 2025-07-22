#include "../inc/Game.hpp"
#include "../inc/GameMap.hpp"
#include "../inc/Player.hpp"
#include <SFML/Graphics.hpp>

sf::RenderWindow window_setup(void) {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode( {SCREEN_WIDTH, SCREEN_HEIGHT} ), "trace95");
	window.setFramerateLimit(144);
	return (window);
}

void raycast(Player& player, const GameMap& gameMap, sf::RenderWindow& window) {
	t_pos p = player.getPosition();
	const auto& map = gameMap.getMap();
	t_rc_params rc_params;

	apply_floor_ceil_colors(gameMap, window);
	draw_crosshair(window);
	for (unsigned int x = 0; x < SCREEN_WIDTH; ++x) {
		compute_raydir(rc_params, x, p);
		init_dda(rc_params, p);
		perform_dda(rc_params, map);
		calc_wall_projection(rc_params);
		apply_wall_textures(rc_params, gameMap, p, x, window);
	}
	draw_minimap(gameMap, window, player);
}