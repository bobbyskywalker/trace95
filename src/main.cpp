#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
# include "../inc/GameMap.hpp"
#include <iostream>

int main(int ac, char **av)
{
	(void) ac; (void) av;
	try {
  		GameMap map = GameMap("../../maps/map1.cub");
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
//	auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "trace95");
//	window.setFramerateLimit(144);
//
//	while (window.isOpen())
//	{
//		while (const std::optional event = window.pollEvent())
//		{
//			if (event->is<sf::Event::Closed>())
//			{
//				window.close();
//			}
//		}
//
//		window.clear();
//		window.display();
//	}
    return (0);
}