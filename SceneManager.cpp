#include "SceneManager.h"

//Define the static bool that allows only one instance of SceneManager to exist
bool SceneManager::m_isInstantiated = false;

//Construct the SceneManager instance, ensuring only one instance can be created
SceneManager::SceneManager(sf::RenderWindow& in_window) 
{
	assert(!m_isInstantiated);
	m_isInstantiated = true;

	//Create the scenes used throughout the game, pass them pointers to the AssetStore and SceneManager instances
	m_scenes["Menu"] = std::make_unique<MenuScene>(MenuScene(&m_assetStore, this));
	m_scenes["Game"] = std::make_unique<GameScene>(GameScene(&m_assetStore, this, in_window.getSize()));

	//Set the starting scene
	m_currentScene = "Game"; //switch to menu
}

//Should the singular SceneManager instance be destroyed, another one can now be created
SceneManager::~SceneManager()
{
	m_isInstantiated = false;
}

void SceneManager::HandleInput(sf::RenderWindow& in_window) 
{
	m_scenes.at(m_currentScene)->HandleInput(in_window);
}

void SceneManager::Update(float const in_deltaTime)
{
	m_scenes.at(m_currentScene)->Update(in_deltaTime);
}

void SceneManager::Draw(sf::RenderWindow& in_window)
{
	m_scenes.at(m_currentScene)->Draw(in_window);
}