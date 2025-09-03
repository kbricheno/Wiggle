#include "InputHandler.h"

void InputHandler::HandleInput(sf::RenderWindow& in_window, std::vector<sf::View*> const in_views)
{
	while (const std::optional event = in_window.pollEvent()) 
	{
		//Closing window
		if (event->is<sf::Event::Closed>())
		{
			in_window.close();
		}

		//Handling key presses
		else if (sf::Event::KeyPressed const *key = event->getIf<sf::Event::KeyPressed>())
		{
			HandleKeyPressed(in_window, key->scancode);
		}

		//Handling key releases
		else if (sf::Event::KeyReleased const *key = event->getIf<sf::Event::KeyReleased>()) 
		{
			HandleKeyReleased(in_window, key->scancode);
		}

		//Handling mouse presses (drag selection in future)
		else if (sf::Event::MouseButtonPressed const* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) 
		{
			HandleMouseButtonDown(in_window, mouseButton->button);
		}

		//Handling mouse releases -- clicking on buttons
		else if (sf::Event::MouseButtonReleased const *mouseButton = event->getIf<sf::Event::MouseButtonReleased>())
		{
			if (mouseButton->button == sf::Mouse::Button::Left) 
			{
				//Check the buttons for each view; views should be passed in in priority order, i.e. UI button click > in-game element click
				for (size_t currentView = in_views.size(); currentView > 0; currentView--)
				{
					sf::Vector2f mousePos = in_window.mapPixelToCoords(sf::Mouse::getPosition(), *in_views.at(currentView));
					
					for (size_t i = 0; i < m_sComps.size(); i++)
					{
						if (m_sComps.at(i)->GetBounds().contains(mousePos)) 
						{
							HandleButtonClickedOn(in_window, m_sComps.at(i));
						}
					}
				}
			}
		}
	}
}