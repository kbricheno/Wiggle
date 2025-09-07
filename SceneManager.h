#pragma once
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include "AssetStore.h"

class Scene;

class SceneManager {
private:
	static bool m_isInstantiated;

	std::map<std::string, std::unique_ptr<Scene>> m_scenes;
	std::string m_currentScene;

	AssetStore m_assetStore;

public:
	SceneManager(sf::RenderWindow& in_window);
	~SceneManager();

	void SetScene(std::string const& in_sceneName);

	void HandleInput(sf::RenderWindow& in_window);
	void Update(float const in_deltaTime);
	void Draw(sf::RenderWindow& in_window);
};