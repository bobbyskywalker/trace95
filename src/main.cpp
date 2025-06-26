# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include "../inc/GameMap.hpp"
# include "../inc/Game.hpp"
# include <iostream>

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Valid exec. ./trace95 <path_to_map>" << std::endl;
		std::exit(1);
	}

	try {
		std::string map_path(av[1]);
		std::ifstream file(map_path);
		if (!file.good())
			throw std::runtime_error("Map file unreadable or non-existent.");
		game_loop(map_path);
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
    return (0);
}