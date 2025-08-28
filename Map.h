#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

class Map {
private:
	std::array<std::array<int, 20>, 12> m_tileGrid;
	sf::Vector2i const m_centerSize = { 3, 3 };
	sf::Vector2i m_centerTile;

	//Quads of Vector2fs representing the texture coordinates for grass tiles -- the quads can be picked at random when creating the background to draw a different grass image
	std::vector<std::array<sf::Vector2f, 4>> m_fogTextureQuads;
	std::vector<std::array<sf::Vector2f, 4>> m_grassTextureQuads;
	std::vector<std::array<sf::Vector2f, 4>> m_markedGrassTextureQuads;
	void PrepareTileMap(int const in_textureTileSize, int const in_numFogTextures, int const in_numGrassTextures, int const in_numMarkedGrassTextures);

	sf::VertexArray m_mapVertices;	
	void GenerateMapVertexArray(int const in_textureTileSize);
	void SetTileTexCoords(sf::Vector2i in_tile);

	void UpdateTerritory();

public:
	Map(int const in_textureTileSize, int const in_numFogTextures, int const in_numGrassTextures, int const in_numMarkedGrassTextures);

	void NotifyNewMarker(sf::Vector2i in_tile);
	void NotifyMarkerDecayed(sf::Vector2i in_tile);
	sf::VertexArray const GetMapVertices() { return m_mapVertices; }

	void PrintMap(); //debug
};