#include "GameInputHandler.h"

void GameInputHandler::HandleButtonClickedOn(sf::RenderWindow& in_window, SelectionComponent in_sCompClicked)
{
	//Check for button-specific behavior e.g. clicking on a "quit" button closes the window 
	m_sceneManager->SetScene("Menu");
}

void GameInputHandler::HandleMouseScrolled(sf::RenderWindow& in_window, bool in_isScrollingUp)
{

}
