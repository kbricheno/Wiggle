#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "AssetStore.h"
#include "GameScene.h"
#include "MenuScene.h"

class SceneManager {
private:
	static bool m_isInstantiated;

	std::map<std::string, std::unique_ptr<Scene>> m_scenes;
	std::string m_currentScene;

	AssetStore m_assetStore;

public:
	SceneManager();
	~SceneManager();

	void SetScene(std::string in_sceneName) { m_currentScene = in_sceneName; };
	std::string const GetScene() { return m_currentScene; };

	void HandleInput(sf::RenderWindow& in_window);
	void Update(float const in_deltaTime);
	void Draw(sf::RenderWindow& in_window);
};