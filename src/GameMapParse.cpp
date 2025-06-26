#include "../inc/GameMap.hpp"

static void trim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return (!std::isspace(ch));
	}));
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return (!std::isspace(ch));
	}).base(), s.end());
}

sf::Color GameMap::_parseColor(const std::string& value) {
	int r, g, b;
	char comma1, comma2;
	std::stringstream ss(value);
	ss >> r >> comma1 >> g >> comma2 >> b;

	if (ss.fail() || comma1 != ',' || comma2 != ',' ||
		r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
			throw std::invalid_argument("Invalid color format: " + value);
		}

	return (sf::Color(r, g, b));
}

bool GameMap::_isMapClosed() const {
	std::size_t height = _2dMap.size();
	if (height == 0)
		return (false);

	std::size_t width = 0;
	for (const std::string& row : _2dMap)
		width = std::max(width, row.length());

	auto checkRow = [](const std::string& row, std::size_t width) {
		for (std::size_t x = 0; x < width; ++x) {
			char tile = (x < row.length()) ? row[x] : ' ';
			if (tile != '1' && tile != ' ')
				return (false);
		}
		return (true);
	};

	if (!checkRow(_2dMap.front(), width) || !checkRow(_2dMap.back(), width))
		return (false);

	for (const std::string& row : _2dMap) {
		int left = 0;
		while (left < (int)row.length() && std::isspace(row[left])) left++;
		if (left >= (int)row.length() || row[left] != '1')
			return (false);

		int right = row.length() - 1;
		while (right >= 0 && std::isspace(row[right])) right--;
		if (right < 0 || row[right] != '1')
			return (false);
	}
	return (true);
}

void GameMap::_validateTextureFile(const std::string& path, const std::string& label) const {
	std::ifstream file(path);
	if (!file.good()) {
		throw std::runtime_error("Texture file not found or unreadable: " + label + " → " + path);
	}
}

void GameMap::_loadTextures(void) {
	if (_NTexturePath.empty())
		throw std::runtime_error("Missing north texture path (NO)");
	if (_STexturePath.empty())
		throw std::runtime_error("Missing south texture path (SO)");
	if (_WTexturePath.empty())
		throw std::runtime_error("Missing west texture path (WE)");
	if (_ETexturePath.empty())
		throw std::runtime_error("Missing east texture path (EA)");

	_validateTextureFile(_NTexturePath, "NO");
	_validateTextureFile(_STexturePath, "SO");
	_validateTextureFile(_WTexturePath, "WE");
	_validateTextureFile(_ETexturePath, "EA");

	if (!_textureNorth.loadFromFile(_NTexturePath))
		throw std::runtime_error("Failed to load texture: NO (" + _NTexturePath + ")");
	if (!_textureSouth.loadFromFile(_STexturePath))
		throw std::runtime_error("Failed to load texture: SO (" + _STexturePath + ")");
	if (!_textureWest.loadFromFile(_WTexturePath))
		throw std::runtime_error("Failed to load texture: WE (" + _WTexturePath + ")");
	if (!_textureEast.loadFromFile(_ETexturePath))
		throw std::runtime_error("Failed to load texture: EA (" + _ETexturePath + ")");

}

t_pos GameMap::_findPlayerTile(void) {
	t_pos res = {0, 0, 0, 0, 0, 0};

	for (std::size_t y = 0; y < _2dMap.size(); ++y) {
		std::string& row = _2dMap[y];
		for (std::size_t x = 0; x < row.length(); ++x) {
			char tile = row[x];
			switch (tile) {
				case 'N':
					res.dirX = 0;
					res.dirY = -1;
					res.planeX = 0.66;
					res.planeY = 0;
					break;
				case 'S':
					res.dirX = 0;
					res.dirY = 1;
					res.planeX = -0.66;
					res.planeY = 0;
					break;
				case 'E':
					res.dirX = 1;
					res.dirY = 0;
					res.planeX = 0;
					res.planeY = 0.66;
					break;
				case 'W':
					res.dirX = -1;
					res.dirY = 0;
					res.planeX = 0;
					res.planeY = -0.66;
					break;
				default:
					continue;
			}
			res.posX = x + 0.5;
			res.posY = y + 0.5;
			row[x] = '0';
			return res;
		}
	}
	throw std::runtime_error("No player start position found in map.");
}



void GameMap::_loadMapFile(void) {
	std::ifstream map_file(_mapFilepath);
	std::string line;

	if (!map_file.is_open())
		throw std::runtime_error("Failed to open map file.");

	bool parsing_map = false;

	while (std::getline(map_file, line)) {
		trim(line);

		if (line.empty())
			continue;

		if (!parsing_map) {
			std::istringstream iss(line);
			std::string identifier;
			iss >> identifier;

			std::string rest;
			std::getline(iss, rest);
			trim(rest);

			if (identifier == "NO") _NTexturePath = rest;
			else if (identifier == "SO") _STexturePath = rest;
			else if (identifier == "WE") _WTexturePath = rest;
			else if (identifier == "EA") _ETexturePath = rest;
			else if (identifier == "F") _floorColor = _parseColor(rest);
			else if (identifier == "C") _ceilColor = _parseColor(rest);
			else if (std::isdigit(line[0]) || line[0] == ' ') {
				parsing_map = true;
				_2dMap.push_back(line);
			}
		} else {
			_2dMap.push_back(line);
		}
	}

	if (!_isMapClosed())
		throw std::runtime_error("Parsed map is not closed.");
	if (_2dMap.empty())
		throw std::runtime_error("No map grid found in file.");

	_loadTextures();

	if (_floorColor == sf::Color(0, 0, 0) && _ceilColor == sf::Color(0, 0, 0)) {
		throw std::runtime_error("Missing floor and ceiling colors");
	}
	else if (_floorColor == sf::Color(0, 0, 0)) {
		throw std::runtime_error("Missing floor color (F)");
	}
	else if (_ceilColor == sf::Color(0, 0, 0)) {
		throw std::runtime_error("Missing ceiling color (C)");
	}

	_playerStartPos = _findPlayerTile();
}
