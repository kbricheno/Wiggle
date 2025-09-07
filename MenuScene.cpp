#include <iostream>
#include "MenuScene.h"

MenuScene::MenuScene()
{
	//Create input handler
	//Create gameobjects & components
}

void MenuScene::Initialize(AssetStore* in_assets, SceneManager* in_sceneManager)
{
	Scene::Initialize(in_assets, in_sceneManager);

	//Initialize menu-specific input handler
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