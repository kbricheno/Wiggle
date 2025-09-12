#include "../InputHandlers/GameInputHandler.h"
#include "../Scenes/GameScene.h"

void GameInputHandler::HandleKeyPressed(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key)
{

}

void GameInputHandler::HandleKeyReleased(sf::RenderWindow& in_window, sf::Keyboard::Scancode const in_key)
{

}

void GameInputHandler::HandleMouseButtonDown(sf::RenderWindow& in_window, sf::Mouse::Button const in_mouseButton)
{

}

void GameInputHandler::HandleButtonClickedOn(sf::RenderWindow& in_window, SelectionComponent& in_sCompClicked)
{

}

void GameInputHandler::HandleMouseScrolled(float in_wheelDelta)
{
	static_cast<GameScene*>(m_scene)->SetMouseScroll(in_wheelDelta);
}

void GameInputHandler::HandleMousePosition(sf::Vector2i in_mousePosInWindow) 
{
	static_cast<GameScene*>(m_scene)->SetMousePos(in_mousePosInWindow);
}