#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Scene.h"

class AssetStore;
class SceneManager;

class MenuScene : public Scene {
private:
	//InputHandler m_inputHandler;

	//std::map<int, GameObject> m_gameObjects;
	//std::map<int, VisualComponent> m_visualComponents;
	//std::map<int, AudioComponent> m_audioComponents;
	//std::map<int, PhysicsComponent> m_physicsComponents;
	//std::map<int, BehaviorComponent> m_behaviorComponents;
	//std::map<int, InputComponent> m_inputComponents;

public:
	MenuScene();

	void Initialize(AssetStore* in_assets, SceneManager* in_sceneManager) override;
	void HandleInput(sf::RenderWindow& in_window) override;
	void Update(sf::RenderWindow& in_window, float const in_deltaTime) override;
	void Draw(sf::RenderWindow& in_window) override;
};