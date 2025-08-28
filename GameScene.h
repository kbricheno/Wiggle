#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Map.h";

class GameScene : public Scene {
private:
	//InputHandler m_inputHandler;
	Map m_map = Map(200, 1, 3, 3);
	
	//std::map<int, GameObject> m_gameObjects;
	//std::map<int, VisualComponent> m_visualComponents;
	//std::map<int, AudioComponent> m_audioComponents;
	//std::map<int, PhysicsComponent> m_physicsComponents;
	//std::map<int, BehaviorComponent> m_behaviorComponents;
	//std::map<int, InputComponent> m_inputComponents;

public:
	GameScene();

	void HandleInput(sf::RenderWindow& in_window) override;
	void Update(float const in_deltaTime) override;
	void Draw(sf::RenderWindow& in_window) override;
};