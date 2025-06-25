# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>
# include "../inc/GameMap.hpp"
# include "../inc/Game.hpp"
# include <iostream>

int main(int ac, char **av)
{
	(void) ac; (void) av;
	try {
		game_loop();
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

    return (0);
}