#include "InputHandler.h"
#include <iostream>

void InputHandler::HandleInput(sf::RenderWindow& in_window, std::map<int,SelectionComponent>& in_sComps)
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
				for (size_t currentView = m_views.size(); currentView > 0; currentView--)
				{
					sf::Vector2f mousePos = in_window.mapPixelToCoords(sf::Mouse::getPosition(), m_views.at(currentView));
					
					for (auto& [id, sComp] : in_sComps)
					{
						if (sComp.GetBounds().contains(mousePos))
						{
							HandleButtonClickedOn(in_window, sComp);
						}
					}
				}
			}
		}

		else if (sf::Event::MouseWheelScrolled const *wheel = event->getIf<sf::Event::MouseWheelScrolled>()) 
		{
			std::cout << wheel->delta << "\n";
			HandleMouseScrolled(in_window, wheel->delta > 0 ? true : false);
		}
	}
}