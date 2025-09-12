#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Scenes/SceneManager.h"

class GameEngine {
private:
	static bool m_isInstantiated;

	sf::Clock m_clock;
	float m_deltaTime = 0;

	//Create the RenderWindow instance which everything will draw to
	sf::RenderWindow m_window = sf::RenderWindow(sf::VideoMode({1200, 800}), "Wiggle", sf::Style::Close, sf::State::Windowed);

	//Create the SceneManager instance which controls what part of the game is currently active
	SceneManager m_sceneManager = SceneManager(m_window);

	void HandleInput();
	void Update();
	void Draw();

public:
	GameEngine();
	~GameEngine();

	void Run();
};