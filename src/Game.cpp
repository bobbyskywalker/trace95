#include "../inc/Game.hpp"
#include "../inc/GameMap.hpp"
#include "../inc/Player.hpp"
#include <SFML/Graphics.hpp>

sf::RenderWindow window_setup(void) {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "trace95");
	window.setFramerateLimit(144);
	return (window);
}

void raycast(Player& player, const GameMap& gameMap, sf::RenderWindow& window) {
    t_pos p = player.getPosition();
    const auto& map = gameMap.getMap();

    for (unsigned int x = 0; x < SCREEN_WIDTH; ++x) {
        double cameraX = 2 * x / static_cast<double>(SCREEN_WIDTH) - 1;
        double rayDirX = p.dirX + p.planeX * cameraX;
        double rayDirY = p.dirY + p.planeY * cameraX;

        int mapX = static_cast<int>(p.posX);
        int mapY = static_cast<int>(p.posY);

        double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

        int stepX, stepY, side = 0;
        double sideDistX, sideDistY;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (p.posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - p.posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (p.posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - p.posY) * deltaDistY;
        }

        bool hit = false;
        while (!hit) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (map[mapY][mapX] == '1')
                hit = true;
        }

        double perpWallDist = (side == 0)
            ? (sideDistX - deltaDistX)
            : (sideDistY - deltaDistY);

        int lineHeight = static_cast<int>(SCREEN_HEIGHT / perpWallDist);
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        int drawEnd   = lineHeight / 2 + SCREEN_HEIGHT / 2;

    	char tile = map[mapY][mapX];
    	sf::Color wallColor;

    	switch (tile) {
    		case '1': wallColor = sf::Color::Red; break;
    		case '2': wallColor = sf::Color::Green; break;
    		case '3': wallColor = sf::Color::Blue; break;
    		case '4': wallColor = sf::Color::White; break;
    		default:  wallColor = sf::Color::Yellow; break;
    	}

    	if (side == 1) {
    		wallColor.r /= 2;
    		wallColor.g /= 2;
    		wallColor.b /= 2;
    	}

        sf::Vertex line[] = {
            { { static_cast<float>(x), static_cast<float>(drawStart) }, wallColor },
            { { static_cast<float>(x), static_cast<float>(drawEnd) },   wallColor }
        };

        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void game_loop(void) {
	auto window = window_setup();

	GameMap map = GameMap("../../maps/map1.cub");
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

			moveSpeed = 5.0f * deltaTime;
			rotSpeed = 5.0f * deltaTime;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
				std::cout << "W pressed\n";
				std::cout << "New pos: " << player.getPosition().posX << ", " << player.getPosition().posY << '\n';
				player.moveForward(moveSpeed, map);
				}
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