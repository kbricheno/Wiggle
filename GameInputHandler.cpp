#include "GameInputHandler.h"
#include "GameScene.h"

void GameInputHandler::HandleKeyPressed(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key)
{

}

void GameInputHandler::HandleKeyReleased(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key)
{

}

void GameInputHandler::HandleMouseButtonDown(sf::RenderWindow& in_window, sf::Mouse::Button const in_mouseButton)
{

}

void GameInputHandler::HandleButtonClickedOn(sf::RenderWindow& in_window, SelectionComponent in_sCompClicked)
{

}

void GameInputHandler::HandleMouseScrolled(sf::RenderWindow& in_window, bool in_isScrollingUp)
{
	static_cast<GameScene*>(m_scene)->ZoomView(in_window, in_isScrollingUp);
}

void GameInputHandler::HandleMousePosition(sf::RenderWindow& in_window, sf::Vector2i in_mousePosInWindow) 
{
	static_cast<GameScene*>(m_scene)->PanView(in_window, in_mousePosInWindow);
}