#include "MenuScene.h"

#include <iostream>


MenuScene::MenuScene(AssetStore* in_assets, SceneManager* in_sceneManager) : Scene(in_assets, in_sceneManager)
{
	//setup input handler
	//spawn gameobjects & components
}

void MenuScene::HandleInput(sf::RenderWindow& in_window)
{
	//inputcomponents.HandleInput(in_window);
	std::cout << "menu input\n";
}

void MenuScene::Update(float const in_deltaTime)
{
	//behaviourcomponents.Update(in_deltaTime);
	//physicscomponents.Update(in_deltaTime);
	//audiocomponents.Update(in_deltaTime);
	std::cout << "menu update\n";
}

void MenuScene::Draw(sf::RenderWindow& in_window)
{
	//visualcomponents.Draw(in_window);
	in_window.display();
	std::cout << "menu draw\n";
}