#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
//u got this <3

class AssetStore;
class SceneManager;

/******************
ABSTRACT BASE CLASS
******************/

class Scene {
protected:
	AssetStore* m_assets = nullptr;
	SceneManager* m_sceneManager = nullptr;

public:
	Scene() {};
	virtual ~Scene() {};

	virtual void Initialize(AssetStore* in_assets, SceneManager* in_sceneManager) {m_assets = in_assets; m_sceneManager = in_sceneManager; }
	virtual void HandleInput(sf::RenderWindow& in_window) = 0;
	virtual void Update(float const in_deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& in_window) = 0;
};