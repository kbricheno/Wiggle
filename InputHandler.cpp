#include "InputHandler.h"

void InputHandler::Initialize(Scene* const in_scene, SceneManager* const in_sceneManager, sf::View* const in_view) 
{
	m_scene = in_scene;
	m_sceneManager = in_sceneManager;
	m_view = in_view;
}

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
		else if (auto const* key = event->getIf<sf::Event::KeyPressed>())
		{
			HandleKeyPressed(in_window, key->scancode);
		}

		//Handling key releases
		else if (auto const* key = event->getIf<sf::Event::KeyReleased>()) 
		{
			HandleKeyReleased(in_window, key->scancode);
		}

		//Handling mouse presses (drag selection in future)
		else if (auto const* mouseButton = event->getIf<sf::Event::MouseButtonPressed>()) 
		{
			HandleMouseButtonDown(in_window, mouseButton->button);
		}

		//Handling mouse releases -- clicking on buttons
		else if (auto const* mouseButton = event->getIf<sf::Event::MouseButtonReleased>())
		{
			if (mouseButton->button == sf::Mouse::Button::Left) 
			{
				sf::Vector2f mousePos = in_window.mapPixelToCoords(sf::Mouse::getPosition(), *m_view);
					
				for (auto& [id, sComp] : in_sComps)
				{
					if (sComp.GetBounds().contains(mousePos))
					{
						HandleButtonClickedOn(in_window, sComp);
					}
				}
			}
		}

		//Handle scroll wheel -- zooms the map in the GameScene
		else if (sf::Event::MouseWheelScrolled const *wheel = event->getIf<sf::Event::MouseWheelScrolled>()) 
		{
			HandleMouseScrolled(in_window, wheel->delta > 0 ? true : false);
		}
	}

	//Always handle mouse position, even if the mouse has not moved (thus outside the event queue)
	//Handle mouse position -- potential to pan the map in the GameScene
	HandleMousePosition(in_window, sf::Mouse::getPosition(in_window));
}