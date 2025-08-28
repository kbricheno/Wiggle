#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

class Map {
private:
	std::array<std::array<int, 20>, 20> m_tileGrid; //Alter the size of the map here
	sf::Vector2i const m_centerSize = { 3, 3 };
	sf::Vector2i m_centerTile;

	//Quads of Vector2fs representing the texture coordinates for tiles -- the quads can be picked at random when creating the background to draw a different grass image
	std::vector<std::array<sf::Vector2f, 4>> m_fogTextureQuads;
	std::vector<std::array<sf::Vector2f, 4>> m_grassTextureQuads;
	std::vector<std::array<sf::Vector2f, 4>> m_markedGrassTextureQuads;
	void PrepareTileTextures(int const in_textureTileSize, int const in_numFogTextures, int const in_numGrassTextures, int const in_numMarkedGrassTextures);

	//VertexArray used to draw the map's various tiles as one entity (more performant than each tile having its own VisualComponent)
	sf::VertexArray m_mapVertices;	
	void GenerateMapVertexArray(int const in_textureTileSize);

	//Manages the territory's borders (absorbs floating fog tiles, removes floating territory blocks, identifies the marker tiles)
	void UpdateTerritory();
	//Sets an individual tile's texture coordinates, called only when a tile's value has changed
	void SetTileTexCoords(sf::Vector2i in_tile);

public:
	Map(int const in_textureTileSize, int const in_numFogTextures, int const in_numGrassTextures, int const in_numMarkedGrassTextures);

	//The Scene must inform the Map instance whenever a tile's state has changed so that the grid and VertexArray can be updated
	void NotifyNewMarker(sf::Vector2i in_tile);
	void NotifyMarkerDecayed(sf::Vector2i in_tile);

	sf::VertexArray const GetMapVertices() { return m_mapVertices; }

	void PrintMap(); //debug
};