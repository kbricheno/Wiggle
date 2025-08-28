#include "Map.h"

//Generate a grid of integers representing tiles, where 0 = fog of war, 1 = territory, and 2 = territory boundary
Map::Map(int const in_textureTileSize, int const in_numFogTextures, int const in_numGrassTextures, int const in_numMarkedGrassTextures)
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

	PrepareTileMap(in_textureTileSize, in_numFogTextures, in_numGrassTextures, in_numMarkedGrassTextures);
	GenerateMapVertexArray(/*in_textureTileSize*/ 50);
	UpdateTerritory();
}

void Map::NotifyNewMarker(sf::Vector2i in_tile) 
{
	//Update the newly marked tile itself
	m_tileGrid.at(in_tile.y).at(in_tile.x) = 2;
	SetTileTexCoords(in_tile);

	//Unmark any territory tiles bordering this new boundary tile
	UpdateTerritory();
}

void Map::NotifyMarkerDecayed(sf::Vector2i in_tile) 
{
	//Update the newly decayed tile itself
	m_tileGrid.at(in_tile.y).at(in_tile.x) = 0;
	SetTileTexCoords(in_tile);

	//Re-establish the territory boundaries and update any other subsequently altered tiles
	UpdateTerritory();
}

//Update the territory, filling in gaps and deleting any territory not connected to the nest
void Map::UpdateTerritory()
{
	//Iterate outward from the nest in a spiral in order to delete territory not connected to the nest
	//The spiral works in sections, where the direction of iteration is changed at the end of a section and the length of the section is increased by 1 every 2 direction changes
	sf::Vector2i direction = { 1,0 };
	int sectionLength = 1;
	sf::Vector2i currentTile = m_centerTile;
	int sectionPos = 0;

	//The spiral works in a square but the grid might be rectangular, so loop through enough tiles to ensure we don't miss any (largest side of the grid squared)
	int loopSize = 0;
	if (m_tileGrid.size() > m_tileGrid.at(0).size()) loopSize = m_tileGrid.size() * m_tileGrid.size();
	else loopSize = m_tileGrid.at(0).size() * m_tileGrid.at(0).size();

	for (int loopPos = 0; loopPos < loopSize; loopPos++)
	{
		//Add the direction vector to the current tile's position, increment the position of the current section
		currentTile += direction;
		sectionPos++;

		//Once we iterate over the last position in the current section, rotate the direction 90 degrees, reset the section position, and increase the section length if necessary
		if (sectionPos == sectionLength) 
		{
			sectionPos = 0;
			int temp = direction.x;
			direction.x = -direction.y;
			direction.y = temp;

			if (direction.y == 0) sectionLength++;
		}

		//Check that the current tile exists (current coordinates might be outside the bounds of a rectangle)
		if (currentTile.y < m_tileGrid.size() && currentTile.x < m_tileGrid.at(0).size()) 
		{
			int tile = m_tileGrid.at(currentTile.y).at(currentTile.x);

			//Obtain the tile's neighbors, also checking that those tiles exist (current tile might be at the very edge of the map)
			std::vector<int> neighborTiles;
			if (currentTile.y + 1 < m_tileGrid.size()) neighborTiles.push_back(m_tileGrid.at(currentTile.y + 1).at(currentTile.x));
			if (currentTile.y - 1 < m_tileGrid.size()) neighborTiles.push_back(m_tileGrid.at(currentTile.y - 1).at(currentTile.x));
			if (currentTile.x + 1 < m_tileGrid.at(0).size()) neighborTiles.push_back(m_tileGrid.at(currentTile.y).at(currentTile.x + 1));
			if (currentTile.x - 1 < m_tileGrid.at(0).size()) neighborTiles.push_back(m_tileGrid.at(currentTile.y).at(currentTile.x - 1));

			//Perform checks on the tile's surroundings to ensure it's of the correct type
			switch (tile)
			{
			case 0: //Fog tile
				//Fog tiles are always fog unless completely encapsulated by territory, in which case they become grass tiles
				if (neighborTiles.size() != 4) break; //It's impossible for edge of map tiles to be completely encapsulated by territory
				if (neighborTiles.at(0) != 0 && neighborTiles.at(1) != 0 && neighborTiles.at(2) != 0 && neighborTiles.at(3) != 0) 
				{
					//Encapsulated tile found -- switch its value to 1
					m_tileGrid.at(currentTile.y).at(currentTile.x) = 1;
					//Update its texture
					SetTileTexCoords(currentTile);
				}
				break;

			case 1: //Grass tile
				//Grass tiles with any fog tile neighbors become marker tiles
				std::cout << "checking grass tile " << currentTile.x << ", " << currentTile.y << ":\n";

				for (int i = 0; i < neighborTiles.size(); i++)
				{
					std::cout << "neighbor " << i << ": " << neighborTiles.at(i) << "\n";
					if (neighborTiles.at(i) == 0) 
					{
						//New marker tile found, update it and its texture
						std::cout << "marker identified, breaking\n";
						m_tileGrid.at(currentTile.y).at(currentTile.x) = 2;
						SetTileTexCoords(currentTile);
						break;
					}
				}
				//Grass tiles that are not connected to the nest by other grass tiles become fog tiles
				break;

			case 2: //Marker tile
				//Marker tiles completely encapsulated by territory become grass tiles
				if (neighborTiles.size() != 4) break; //It's impossible for edge of map tiles to be completely encapsulated by territory
				if (neighborTiles.at(0) != 0 && neighborTiles.at(1) != 0 && neighborTiles.at(2) != 0 && neighborTiles.at(3) != 0)
				{
					//Encapsulated tile found -- switch its value to 1
					m_tileGrid.at(currentTile.y).at(currentTile.x) = 1;
					//Update its texture
					SetTileTexCoords(currentTile);
				}
				break;

			default: //More tiles go here
				break;
			}
		}
	}
}

//Slice the map texture up into tiles and store their coordinates for the VertexArray to use
void Map::PrepareTileMap(int const in_textureTileSize, int const in_numFogTextures, int const in_numGrassTextures, int const in_numMarkedGrassTextures) 
{
	int totalTextures = in_numFogTextures + in_numGrassTextures + in_numMarkedGrassTextures;
	for (int i = 0; i < totalTextures; i++)
	{
		if (i < in_numFogTextures)
		{
			m_fogTextureQuads.push_back(
			{
				sf::Vector2f(0 + (i * in_textureTileSize), 0),
				sf::Vector2f(0 + (i * in_textureTileSize), in_textureTileSize),
				sf::Vector2f(in_textureTileSize + (i * in_textureTileSize), 0),
				sf::Vector2f(in_textureTileSize + (i * in_textureTileSize), in_textureTileSize)
			});
		}
		else if (i < in_numGrassTextures) 
		{
			m_grassTextureQuads.push_back(
			{
				sf::Vector2f(0 + (i * in_textureTileSize), 0),
				sf::Vector2f(0 + (i * in_textureTileSize), in_textureTileSize),
				sf::Vector2f(in_textureTileSize + (i * in_textureTileSize), 0),
				sf::Vector2f(in_textureTileSize + (i * in_textureTileSize), in_textureTileSize)
			});
		}
		else 
		{
			m_markedGrassTextureQuads.push_back(
			{
				sf::Vector2f(0 + (i * in_textureTileSize), 0),
				sf::Vector2f(0 + (i * in_textureTileSize), in_textureTileSize),
				sf::Vector2f(in_textureTileSize + (i * in_textureTileSize), 0),
				sf::Vector2f(in_textureTileSize + (i * in_textureTileSize), in_textureTileSize)
			});
		}
	}
}

//Set the position and texture coordinates for each triangle in the map's VertexArray
void Map::GenerateMapVertexArray(int const in_textureTileSize)
{
	int const mapHeight = m_tileGrid.size();
	int const mapWidth = m_tileGrid.at(0).size();

	//Set up the VertexArray
	m_mapVertices.setPrimitiveType(sf::PrimitiveType::Triangles);
	m_mapVertices.resize(mapWidth * mapHeight * 6);
	std::cout << "height: " << mapHeight << ", width: " << mapWidth << ", num tiles: " << mapHeight * mapWidth << "\n";

	//Loop the map grid
	for (int currentY = 0; currentY < mapHeight; ++currentY)
	{
		for (int currentX = 0; currentX < mapWidth; ++currentX)
		{
			//Get a pointer to the triangles' vertices of the current tile
			sf::Vertex* triangles = &m_mapVertices[(currentX + currentY * mapWidth) * 6];

			//Set the positions of the corners making up the 2 triangles
			triangles[0].position = sf::Vector2f(currentX * in_textureTileSize, currentY * in_textureTileSize);
			triangles[1].position = sf::Vector2f((currentX + 1) * in_textureTileSize, currentY * in_textureTileSize);
			triangles[2].position = sf::Vector2f(currentX * in_textureTileSize, (currentY + 1) * in_textureTileSize);
			triangles[3].position = sf::Vector2f(currentX * in_textureTileSize, (currentY + 1) * in_textureTileSize);
			triangles[4].position = sf::Vector2f((currentX + 1) * in_textureTileSize, currentY * in_textureTileSize);
			triangles[5].position = sf::Vector2f((currentX + 1) * in_textureTileSize, (currentY + 1) * in_textureTileSize);

			//Set the texture coordinates for this tile
			SetTileTexCoords({ currentX, currentY });
		}
	}
}

//Sets an individual tile's texture coordinates -- to be used ONLY when a tile's type has changed (e.g. from fog of war (0) to marked grass (1))
void Map::SetTileTexCoords(sf::Vector2i in_tile) 
{
	//Switch the current tile value, set the vertices of the current tile's texture coordinates based on the type of tile the number represents			
	std::array<sf::Vector2f, 4> textureQuad;

	switch (m_tileGrid.at(in_tile.y).at(in_tile.x))
	{
	case 0:
		//Fog of war tile
		textureQuad = m_fogTextureQuads.at(rand() % m_fogTextureQuads.size());
		break;

	case 1:
		//Grass tile
		textureQuad = m_grassTextureQuads.at(rand() % m_grassTextureQuads.size());
		break;

	case 2:
		//Marked grass tile
		textureQuad = m_markedGrassTextureQuads.at(rand() % m_markedGrassTextureQuads.size());
		break;

		//Potential future tile types go here
	default:
		break;
	}

	//Get a pointer to the triangles' vertices of the current tile
	sf::Vertex* triangles = &m_mapVertices[(in_tile.x + in_tile.y * m_tileGrid.at(0).size()) * 6];

	triangles[0].texCoords = textureQuad[0];
	triangles[1].texCoords = textureQuad[2];
	triangles[2].texCoords = textureQuad[1];
	triangles[3].texCoords = textureQuad[1];
	triangles[4].texCoords = textureQuad[2];
	triangles[5].texCoords = textureQuad[3];
}

void Map::PrintMap()
{
	for (int height = 0; height < m_tileGrid.size(); height++)
	{
		for (int width = 0; width < m_tileGrid.at(0).size(); width++)
		{
			if (width == m_tileGrid.at(0).size() - 1) std::cout << m_tileGrid.at(height).at(width) << "\n";
			else std::cout << m_tileGrid.at(height).at(width) << " ";
		}
	}
}