#include "GameScene.h"
#include <iostream>

GameScene::GameScene() 
{
	//setup input handler
	//setup map
	m_map.PrintMap(); //ensure the map was generated correctly
	//spawn gameobjects & components
}

void GameScene::HandleInput(sf::RenderWindow& in_window) 
{
	//inputcomponents.HandleInput(in_window);
}

void GameScene::Update(float const in_deltaTime)
{
	//behaviourcomponents.Update(in_deltaTime);
	//physicscomponents.Update(in_deltaTime);
	//audiocomponents.Update(in_deltaTime);
}

void GameScene::Draw(sf::RenderWindow& in_window)
{
	//visualcomponents.Draw(in_window);

	//sf::VertexArray bgRow(sf::PrimitiveType::TriangleStrip, 20 * 4);
	////Quads of Vector2fs representing the texture coordinates for grass tiles -- the quads can be picked at random when creating the background to draw a different grass image
	//std::vector<std::array<sf::Vector2f, 4>> textureQuads = {
	//	{
	//		sf::Vector2f(200, 0),
	//		sf::Vector2f(200, 200),
	//		sf::Vector2f(400, 0),
	//		sf::Vector2f(400, 200)
	//	},
	//	{	
	//		sf::Vector2f(400, 0),
	//		sf::Vector2f(400, 200),
	//		sf::Vector2f(600, 0),
	//		sf::Vector2f(600, 200)	
	//	},
	//	{
	//		sf::Vector2f(600, 0),
	//		sf::Vector2f(600, 200),
	//		sf::Vector2f(800, 0),
	//		sf::Vector2f(800, 200)
	//	},
	//};

	//std::array<sf::Vector2f, 4> quadPositions = {
	//	sf::Vector2f(0,0),
	//	sf::Vector2f(0,200),
	//	sf::Vector2f(200,0),
	//	sf::Vector2f(200,200)
	//};

	//int tileTex = 0;
	//for (int i = 0; i < bgRow.getVertexCount(); i++)
	//{
	//	if (i % 4 == 0) //every 4th vertex = the start of a new quad
	//	{
	//		tileTex = (tileTex + 1) % 3;
	//	}

	//	if (i < 4) 
	//	{
	//		bgRow[i].position = quadPositions[i % 4];
	//	}
	//	else
	//	{
	//		bgRow[i].position = { bgRow[i - 4].position.x + 200, bgRow[i - 4].position.y };
	//	}

	//	bgRow[i].texCoords = textureQuads.at(tileTex)[i % 4];
	//}

	sf::Texture bgTex = m_assets->GetBitmap("grass");
	in_window.draw(m_map.GetMapVertices(), &bgTex);
}