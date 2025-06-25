#ifndef MAP_HPP
# define MAP_HPP

# include <string>
# include <vector>
# include <string>
# include <fstream>
# include <stdexcept>
# include <sstream>
# include <vector>
# include <cctype>
# include <algorithm>
# include <SFML/Graphics.hpp>

class GameMap {

private:
	std::vector<std::string> 				_2dMap;
	std::string								_mapFilepath;

	std::string 							_NTexture;
	std::string 							_STexture;
	std::string 							_WTexture;
	std::string 							_ETexture;

   	sf::Color 								_floorColor;
	sf::Color 								_ceilColor;

	bool									_isMapClosed(void) const;
	void									_validateTextureFile(const std::string& path, const std::string& label) const;
	sf::Color 								_parseColor(const std::string& value);
	void									_loadMapFile(void);

public:
	GameMap(const std::string& map_filepath);
    ~GameMap(void);

    const std::vector<std::string>&  		getMap(void) const;
    const std::string& 						getTexture(char id) const;
    const sf::Color 						getFloorColor(void) const;
	const sf::Color 						getCeilColor(void) const;
} ;

#endif
