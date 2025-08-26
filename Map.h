#pragma once
#include <SFML/System.hpp>

#include <iostream>

class Map {
private:
	std::array<std::array<int, 20>, 20> m_tileGrid;
	sf::Vector2i const m_centerSize = { 3, 3 };
	sf::Vector2i m_centerTile;

public:
	Map();
	std::vector<sf::Vector2i> GetTerritoryBoundaries();
	void PrintMap(std::vector<sf::Vector2i> in_boundaries);
};