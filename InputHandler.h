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
	//Store a vector of pointers to each SelectionComponent in the Scene to identify which entity has been clicked on
	std::vector<SelectionComponent*> m_sComps;

	//Specific responses to input overridden in derived InputHandlers
	virtual void HandleKeyPressed(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key) {};
	virtual void HandleKeyReleased(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key) {};
	virtual void HandleMouseButtonDown(sf::RenderWindow& in_window, sf::Mouse::Button const in_mouseButton) {};
	virtual void HandleButtonClickedOn(sf::RenderWindow& in_window, SelectionComponent* in_buttonClicked) {};


public:
	InputHandler(Scene* in_scene, SceneManager* in_sceneManager, std::vector<SelectionComponent*> in_sComps)
	: m_scene(in_scene), m_sceneManager(in_sceneManager), m_sComps(in_sComps) {};

	void HandleInput(sf::RenderWindow& in_window, std::vector<sf::View*> const in_views);
};