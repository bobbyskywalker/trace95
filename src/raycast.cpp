#include "../inc/Game.hpp"
#include "../inc/GameMap.hpp"
#include "../inc/Player.hpp"
#include <SFML/Graphics.hpp>

sf::RenderWindow window_setup(void) {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "trace95");
	window.setFramerateLimit(144);
	return (window);
}

static void compute_raydir(t_rc_params& rc_params, unsigned int x, t_pos& p) {
	rc_params.cameraX = 2 * x / static_cast<double>(SCREEN_WIDTH) - 1;
	rc_params.rayDirX = p.dirX + p.planeX * rc_params.cameraX;
	rc_params.rayDirY = p.dirY + p.planeY * rc_params.cameraX;

	rc_params.mapX = static_cast<int>(p.posX);
	rc_params.mapY = static_cast<int>(p.posY);

	rc_params.deltaDistX = (rc_params.rayDirX == 0) ? 1e30 : std::abs(1 / rc_params.rayDirX);
	rc_params.deltaDistY = (rc_params.rayDirY == 0) ? 1e30 : std::abs(1 / rc_params.rayDirY);
}

static void init_dda(t_rc_params& rc_params, t_pos& p) {
	rc_params.stepX = 0;
	rc_params.stepY = 0;
	rc_params.side = 0;

	rc_params.sideDistX = 0;
	rc_params.sideDistY = 0;

	if (rc_params.rayDirX < 0) {
		rc_params.stepX = -1;
		rc_params.sideDistX = (p.posX - rc_params.mapX) * rc_params.deltaDistX;
	} else {
		rc_params.stepX = 1;
		rc_params.sideDistX = (rc_params.mapX + 1.0 - p.posX) * rc_params.deltaDistX;
	}
	if (rc_params.rayDirY < 0) {
		rc_params.stepY = -1;
		rc_params.sideDistY = (p.posY - rc_params.mapY) * rc_params.deltaDistY;
	} else {
		rc_params.stepY = 1;
		rc_params.sideDistY = (rc_params.mapY + 1.0 - p.posY) * rc_params.deltaDistY;
	}
}

static void perform_dda(t_rc_params& rc_params, const std::vector<std::string> & map) {
	bool hit = false;
	while (!hit) {
		if (rc_params.sideDistX < rc_params.sideDistY) {
			rc_params.sideDistX += rc_params.deltaDistX;
			rc_params.mapX += rc_params.stepX;
			rc_params.side = 0;
		} else {
			rc_params.sideDistY += rc_params.deltaDistY;
			rc_params.mapY += rc_params.stepY;
			rc_params.side = 1;
		}
		if (map[rc_params.mapY][rc_params.mapX] == '1')
			hit = true;
	}
}

void calc_wall_projection(t_rc_params& rc_params) {
	rc_params.perpWallDist = (rc_params.side == 0)
			? (rc_params.sideDistX - rc_params.deltaDistX)
			: (rc_params.sideDistY - rc_params.deltaDistY);

	rc_params.lineHeight = static_cast<int>(SCREEN_HEIGHT / rc_params.perpWallDist);
	rc_params.drawStart = -rc_params.lineHeight / 2 + SCREEN_HEIGHT / 2;
}

void raycast(Player& player, const GameMap& gameMap, sf::RenderWindow& window) {
	t_pos p = player.getPosition();
	const auto& map = gameMap.getMap();
	t_rc_params rc_params;

	for (unsigned int x = 0; x < SCREEN_WIDTH; ++x) {
		compute_raydir(rc_params, x, p);
		init_dda(rc_params, p);
		perform_dda(rc_params, map);
		calc_wall_projection(rc_params);

		char wallSide;
		if (rc_params.side == 0)
			wallSide = (rc_params.rayDirX > 0) ? 'W' : 'E';
		else
			wallSide = (rc_params.rayDirY > 0) ? 'N' : 'S';

		const sf::Texture& tex = gameMap.getTexture(wallSide);
		int texWidth = tex.getSize().x;
		int texHeight = tex.getSize().y;

		double wallX = (rc_params.side == 0)
			? p.posY + rc_params.perpWallDist * rc_params.rayDirY
			: p.posX + rc_params.perpWallDist * rc_params.rayDirX;
		wallX -= floor(wallX);

		int texX = static_cast<int>(wallX * texWidth);
		if (rc_params.side == 0 && rc_params.rayDirX > 0) texX = texWidth - texX - 1;
		if (rc_params.side == 1 && rc_params.rayDirY < 0) texX = texWidth - texX - 1;

		sf::Sprite slice(tex);
		slice.setTextureRect({{texX, 0}, {1, texHeight}});
		slice.setScale({1.f, float(rc_params.lineHeight) / texHeight});
		slice.setPosition({float(x), float(rc_params.drawStart)});
		window.draw(slice);
	}
}