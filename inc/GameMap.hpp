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
# include "Utils.hpp"

class GameMap {

private:
	std::vector<std::string> 				_2dMap;
	std::string								_mapFilepath;

	t_pos									_playerStartPos;

	std::string 							_NTexturePath;
	std::string 							_STexturePath;
	std::string 							_WTexturePath;
	std::string 							_ETexturePath;
	sf::Texture 							_textureNorth;
	sf::Texture 							_textureSouth;
	sf::Texture 							_textureWest;
	sf::Texture 							_textureEast;

   	sf::Color 								_floorColor;
	sf::Color 								_ceilColor;

	bool									_isMapClosed(void) const;
	void									_validateTextureFile(const std::string& path, const std::string& label) const;
	void 									_loadTextures(void);
	sf::Color 								_parseColor(const std::string& value);
	t_pos 									_findPlayerTile(void);
	void									_loadMapFile(void);

public:
	GameMap(const std::string& map_filepath);
    ~GameMap(void);

    const std::vector<std::string>&  		getMap(void) const;
    const std::string& 						getTexturePath(char id) const;
	const sf::Texture& 						getTexture(char side) const;
    const sf::Color 						getFloorColor(void) const;
	const sf::Color 						getCeilColor(void) const;
	const t_pos&							getPlayerStartPos(void) const;
} ;

#endif
