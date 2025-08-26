#include "Map.h"

//Generate a grid of integers representing tiles, where 0 = fog of war, 1 = territory, and 2 = territory boundary
Map::Map() 
{
	//Check for invalid map and/or starting territory size, print text to explain subsequent crash
	if (m_centerSize.y > m_tileGrid.size() || m_centerSize.x > m_tileGrid.at(0).size())
	{
		std::cout << "Starting territory is greater than the size of the entire map -- please adjust values.\n";
	}

	//Generate the initial grid
	for (int height = 0; height < m_tileGrid.size(); height++)
	{
		for (int width = 0; width < m_tileGrid.at(0).size(); width++)
		{
			m_tileGrid.at(height).at(width) = 0;
		}
	}

	//Find the tile in the center of the grid
	m_centerTile = { (int)std::ceil(m_tileGrid.at(0).size() / 2.f), (int)std::ceil(m_tileGrid.size() / 2.f)};

	//Identify the starting territory tiles in the grid
	sf::Vector2i centerTileOffset = { (int)std::floor(m_centerTile.x - (m_centerSize.x / 2.f)), (int)std::floor(m_centerTile.y - (m_centerSize.y / 2.f)) };
	for (int width = 0; width < m_centerSize.x; width++)
	{
		for (int height = 0; height < m_centerSize.y; height++)
		{
			m_tileGrid.at(centerTileOffset.y + height).at(centerTileOffset.x + width) = 1;
		}
	}
}

std::vector<sf::Vector2i> Map::GetTerritoryBoundaries()
{
	std::vector<sf::Vector2i> boundaries;

	for (int height = 0; height < m_tileGrid.size(); height++)
	{
		for (int width = 0; width < m_tileGrid.at(0).size(); width++)
		{
			if (m_tileGrid.at(height).at(width) == 1)
			{
				if (m_tileGrid.at(height + 1).at(width) == 0) boundaries.push_back({ width, height });
				if (m_tileGrid.at(height - 1).at(width) == 0) boundaries.push_back({ width, height });
				if (m_tileGrid.at(height).at(width + 1) == 0) boundaries.push_back({ width, height });
				if (m_tileGrid.at(height).at(width - 1) == 0) boundaries.push_back({ width, height });
			}
		}
	}

	return boundaries;
}

void Map::PrintMap(std::vector<sf::Vector2i> in_boundaries) 
{
	//Make the boundaries visible
	for (int i = 0; i < in_boundaries.size(); i++)
	{
		m_tileGrid.at(in_boundaries.at(i).y).at(in_boundaries.at(i).x) = 2;
	}

	for (int height = 0; height < m_tileGrid.size(); height++)
	{
		for (int width = 0; width < m_tileGrid.at(0).size(); width++)
		{
			if (width == m_tileGrid.at(0).size() - 1) std::cout << m_tileGrid.at(height).at(width) << "\n";
			else std::cout << m_tileGrid.at(height).at(width) << " ";
		}
	}
}