#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "SceneManager.h"

class GameEngine {
private:
	static bool m_isInstantiated;

	sf::Clock m_clock;
	float m_deltaTime = 0;
	sf::RenderWindow m_window = sf::RenderWindow(sf::VideoMode({1200, 800}), "Wiggle", sf::Style::Close, sf::State::Windowed);

	SceneManager m_sceneManager = SceneManager(m_window);

	void HandleInput();
	void Update();
	void Draw();

public:
	GameEngine();
	~GameEngine();

	void Run();
};