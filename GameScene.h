#pragma once
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include "Scene.h"
#include "Map.h"
#include "GameInputHandler.h"
#include "SelectionComponent.h"

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
	float m_viewScroll = 10.f;
	float const m_VIEW_SCROLL_INCREMENT = 0.25f;
	sf::Vector2f const m_VIEW_SCROLL_BOUNDS = { 5.f, 30.f };
	int const m_VIEW_MOVE_BOUNDS = 75;
	float const m_VIEW_MOVE_SPEED = 1.f;
	
	//std::map<int, GameObject> m_gameObjects;
	//std::map<int, VisualComponent> m_visualComponents;
	//std::map<int, AudioComponent> m_audioComponents;
	//std::map<int, PhysicsComponent> m_physicsComponents;
	//std::map<int, BehaviorComponent> m_behaviorComponents;
	std::map<int, SelectionComponent> m_selectionComponents;


public:
	GameScene(sf::Vector2u const in_windowSize);
	
	void Initialize(AssetStore* in_assets, SceneManager* in_sceneManager) override;
	void HandleInput(sf::RenderWindow& in_window) override;
	void Update(float const in_deltaTime) override;
	void Draw(sf::RenderWindow& in_window) override;

	void ZoomView(sf::RenderWindow& in_window, bool in_isZoomingIn);
	void PanView(sf::RenderWindow& in_window, sf::Vector2i in_mousePosInWindow);

	void PrintW() { std::cout << "pressed w on scene"; }
};