#pragma once
#include <SFML/Graphics.hpp>
#include "AssetStore.h"
//u got this <3

class SceneManager;

/******************
ABSTRACT BASE CLASS
******************/

class Scene {
protected:
	AssetStore* m_assets;
	SceneManager* m_sceneManager;

public:
	Scene(AssetStore* in_assets, SceneManager* in_sceneManager) : m_assets(in_assets), m_sceneManager(in_sceneManager) {};
	virtual ~Scene() {};

	virtual void HandleInput(sf::RenderWindow& in_window) = 0;
	virtual void Update(float const in_deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& in_window) = 0;
};