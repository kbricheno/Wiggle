#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "SelectionComponent.h"

class InputHandler {
protected:
	//Store a pointer to the active Scene to return commands to
	Scene* m_scene;
	//Store a pointer to the SceneManager to return the command to switch Scene to
	SceneManager* m_sceneManager;
	//Store a pointer to the active Scene's Views to compare the mouse position to; views should be passed in in priority order, i.e. UI button click > in-game element click
	std::vector<sf::View> m_views;

	//Specific responses to input overridden in derived InputHandlers
	virtual void HandleKeyPressed(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key) {};
	virtual void HandleKeyReleased(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key) {};
	virtual void HandleMouseButtonDown(sf::RenderWindow& in_window, sf::Mouse::Button const in_mouseButton) {};
	virtual void HandleButtonClickedOn(sf::RenderWindow& in_window, SelectionComponent in_sCompClicked) {};
	virtual void HandleMouseScrolled(sf::RenderWindow& in_window, bool in_isScrollingUp) {};

public:
	InputHandler(Scene* const in_scene, SceneManager* const in_sceneManager, std::vector<sf::View> const in_views)
	: m_scene(in_scene), m_sceneManager(in_sceneManager), m_views(in_views) {};

	void HandleInput(sf::RenderWindow& in_window, std::map<int,SelectionComponent>& in_sComps);
};