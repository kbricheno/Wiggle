#pragma once
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include "Scene.h"
#include "../Map.h"
#include "../InputHandlers/GameInputHandler.h"
#include "../Components/GameObject.h"
#include "../Components/SelectionComponent.h"

#include <iostream>

class AssetStore;
class SceneManager;

class GameScene : public Scene {
private:
	//Map
	int const m_TILE_SIZE = 200;
	Map m_map = Map(m_TILE_SIZE, 1, 3, 3);

	//Create game-specific input handler
	GameInputHandler m_inputHandler;


	//View-related attributes allowing the user to pan the view around and zoom in/out
	sf::View m_gameView;

	int m_mouseWheelDelta = 0;
	float m_currentViewZoom = 10.f;
	float const m_VIEW_SCROLL_INCREMENT = 50.f;
	sf::Vector2f const m_VIEW_SCROLL_BOUNDS = { 5.f, 30.f };
	void PanView(sf::RenderWindow const& in_window, float const in_deltaTime);

	sf::Vector2i m_mousePosInWindow;
	int const m_VIEW_MOVE_BOUNDS = 75;
	float const m_VIEW_MOVE_SPEED = 750.f;
	void ZoomView(sf::RenderWindow const& in_window, float const in_deltaTime);

	

	int currentId = 0;
	std::map<int, GameObject> m_gameObjects;
	//std::map<int, VisualComponent> m_visualComponents;
	//std::map<int, AudioComponent> m_audioComponents;
	//std::map<int, PhysicsComponent> m_physicsComponents;
	//std::map<int, BehaviorComponent> m_behaviorComponents;
	std::map<int, SelectionComponent> m_selectionComponents;


public:
	GameScene(sf::RenderWindow const& in_window);
	
	void Initialize(AssetStore* in_assets, SceneManager* in_sceneManager) override;
	void HandleInput(sf::RenderWindow& in_window) override;
	void Update(sf::RenderWindow& in_window, float const in_deltaTime) override;
	void Draw(sf::RenderWindow& in_window) override;

	//Methods called by the InputHandler instance to update the GameScene about mouse position and scroll wheel inputs
	void SetMouseScroll(int in_mouseWheelDelta) { m_mouseWheelDelta = in_mouseWheelDelta; }
	void SetMousePos(sf::Vector2i in_mousePosInWindow) { m_mousePosInWindow = in_mousePosInWindow; }
};