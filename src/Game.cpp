#include "../inc/Game.hpp"
#include "../inc/GameMap.hpp"
#include "../inc/Player.hpp"
#include <SFML/Graphics.hpp>

void game_loop(std::string& map_path) {
	auto window = window_setup();

	GameMap map = GameMap(map_path);
	Player player = Player(map);

	sf::Clock clock;
	float deltaTime;

	float moveSpeed;
	float rotSpeed;

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}

		deltaTime = clock.restart().asSeconds();

		moveSpeed = 5.0f * deltaTime;
		rotSpeed = 5.0f * deltaTime;

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
		}
		window.clear();
		deltaTime = clock.restart().asSeconds();

		raycast(player, map, window);

		window.display();
	}
}