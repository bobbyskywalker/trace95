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

void GameMap::_loadMapFile(void) {
	std::ifstream map_file(_mapFilepath);
	std::string line;

	if (!map_file.is_open())
		throw std::runtime_error("Failed to open map file.");

	bool parsing_map = false;

	while (std::getline(map_file, line)) {
		trim(line);

		if (line.empty()) continue;

		if (!parsing_map) {
			if (line.rfind("NO ", 0) == 0) _NTexture = line.substr(3);
			else if (line.rfind("SO ", 0) == 0) _STexture = line.substr(3);
			else if (line.rfind("WE ", 0) == 0) _WTexture = line.substr(3);
			else if (line.rfind("EA ", 0) == 0) _ETexture = line.substr(3);
			else if (line.rfind("F ", 0) == 0) _floorColor = _parseColor(line.substr(2));
			else if (line.rfind("C ", 0) == 0) _ceilColor = _parseColor(line.substr(2));
			else if (std::isdigit(line[0]) || line[0] == ' ') {
				parsing_map = true;
				_2dMap.push_back(line);
			}
		} else {
			_2dMap.push_back(line);
		}
	}

	if (_2dMap.empty())
		throw std::runtime_error("No map grid found in file.");
	if (_NTexture.empty())
		throw std::runtime_error("Missing north texture path (NO)");
	if (_STexture.empty())
		throw std::runtime_error("Missing south texture path (SO)");
	if (_WTexture.empty())
		throw std::runtime_error("Missing west texture path (WE)");
	if (_ETexture.empty())
		throw std::runtime_error("Missing east texture path (EA)");
}