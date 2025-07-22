#include "../inc/GameMap.hpp"
#include "../inc/Player.hpp"
#include <iostream>

void draw_minimap(const GameMap &gameMap, sf::RenderWindow &window, Player &player) {
	std::vector<std::string> map = gameMap.getMap();
	const t_pos &player_pos = player.getPosition();
	float tile_size = 5.0;

	for (std::size_t y = 0; y < map.size(); ++y) {
		for (std::size_t x = 0; x < map[y].length(); ++x) {
			if (map[y][x] == '1') {
				sf::CircleShape dot(tile_size / 2);
				dot.setFillColor(sf::Color::White);
				dot.setPosition( {x * tile_size, y * tile_size} );
				window.draw(dot);
			}
		}
	}
	sf::CircleShape player_dot(tile_size / 2);
	player_dot.setFillColor(sf::Color::Red);
	float px = static_cast<float>(player_pos.posX * tile_size);
	float py = static_cast<float>(player_pos.posY * tile_size);
	player_dot.setPosition(sf::Vector2f(px, py));
	window.draw(player_dot);
}
