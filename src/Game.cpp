#include "../inc/Game.hpp"
#include "../inc/GameMap.hpp"
#include "../inc/Player.hpp"
#include <SFML/Graphics.hpp>

void game_loop(std::string& map_path) {
	auto window = window_setup();

	GameMap map(map_path);
	Player player(map);

	sf::Clock clock;
	float deltaTime;

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		deltaTime = clock.restart().asSeconds();

		float moveSpeed = 3.0f * deltaTime;
		float rotSpeed = 3.0f * deltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			player.moveForward(moveSpeed, map);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			player.moveBackward(moveSpeed, map);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			player.strafeLeft(moveSpeed, map);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			player.strafeRight(moveSpeed, map);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			player.rotate(-rotSpeed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			player.rotate(rotSpeed);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			window.close();

		window.clear();
		raycast(player, map, window);
		draw_crosshair(window);
		window.display();
	}
}
