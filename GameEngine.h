#pragma once
#include <SFML/Graphics.hpp>
#include "SceneManager.h"

class GameEngine {
private:
	static bool m_isInstantiated;

	sf::Clock m_clock;
	float m_deltaTime = 0;
	sf::RenderWindow m_window;

	SceneManager m_sceneManager;

	void HandleInput();
	void Update();
	void Draw();

public:
	GameEngine();
	~GameEngine();

	void Run();
};