#pragma once
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../Components/SelectionComponent.h"

class Scene;
class SceneManager;

class InputHandler {
protected:
	//Store a pointer to the active Scene to return commands to
	Scene* m_scene = nullptr;
	//Store a pointer to the SceneManager to return the command to switch Scene to
	SceneManager* m_sceneManager = nullptr;
	//Store a pointer to the View this input handler will interact through
	sf::View* m_view = nullptr;

	//Specific responses to input overridden in derived InputHandlers
	virtual void HandleKeyPressed(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key) {};
	virtual void HandleKeyReleased(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key) {};
	virtual void HandleMouseButtonDown(sf::RenderWindow& in_window, sf::Mouse::Button const in_mouseButton) {};
	virtual void HandleButtonClickedOn(sf::RenderWindow& in_window, SelectionComponent& in_sCompClicked) {};

	float m_wheelDelta = 0;
	void SetMouseScrolled(float in_wheelDelta) { m_wheelDelta = in_wheelDelta; }
	sf::Vector2i m_mousePosInWindow = { 0,0 };
	void SetMousePosition(sf::Vector2i in_mousePosInWindow) { m_mousePosInWindow = in_mousePosInWindow; }

public:
	InputHandler() {};

	void Initialize(Scene* const in_scene, SceneManager* const in_sceneManager, sf::View* const in_view);
	void HandleInput(sf::RenderWindow& in_window, std::map<int,SelectionComponent>& in_sComps);

	float GetWheelDelta() { return m_wheelDelta; }
	sf::Vector2i GetMousePosition() { return m_mousePosInWindow; }
};