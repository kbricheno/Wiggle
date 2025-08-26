#include "GameScene.h"
#include <iostream>

GameScene::GameScene() 
{
	//setup input handler
	//setup map
	m_map.PrintMap(m_map.GetTerritoryBoundaries()); //ensure the map was generated correctly
	//spawn gameobjects & components
}

void GameScene::HandleInput(sf::RenderWindow& in_window) 
{
	//inputcomponents.HandleInput(in_window);
	std::cout << "game input\n";
}

void GameScene::Update(float const in_deltaTime)
{
	//behaviourcomponents.Update(in_deltaTime);
	//physicscomponents.Update(in_deltaTime);
	//audiocomponents.Update(in_deltaTime);

	std::cout << "game input\n";
}

void GameScene::Draw(sf::RenderWindow& in_window)
{
	//visualcomponents.Draw(in_window);

	std::cout << "game input\n";
}