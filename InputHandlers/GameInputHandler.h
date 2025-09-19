#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "InputHandler.h"
#include "../Components/SelectionComponent.h"

class GameInputHandler : public InputHandler {
private:
	void HandleKeyPressed(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key) override;
	void HandleKeyReleased(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key) override;
	void HandleMouseButtonDown(sf::RenderWindow& in_window, sf::Mouse::Button const in_mouseButton) override;
	void HandleButtonClickedOn(sf::RenderWindow& in_window, SelectionComponent& in_sCompClicked) override;

public:
	GameInputHandler() {}
};