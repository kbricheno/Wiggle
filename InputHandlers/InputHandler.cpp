#include "InputHandler.h"
#include <iostream>

void InputHandler::Initialize(Scene* const in_scene, SceneManager* const in_sceneManager, sf::View* const in_view) 
{
	m_scene = in_scene;
	m_sceneManager = in_sceneManager;
	m_view = in_view;
}

void InputHandler::HandleInput(sf::RenderWindow& in_window, std::map<int,SelectionComponent>& in_sComps)
{
	//Always store mouse position, even if the mouse has not moved (thus outside the event queue)
	//Store the mouse position value which can be read by other classes
	SetMousePosition(sf::Mouse::getPosition(in_window));

	//Reset the mouse's wheel value to 0
	SetMouseScrolled(0.f);

	//Update each SelectionComponent's hovered bool
	for (auto& [id, sComp] : in_sComps)
	{
		sComp.SetHovered(false);
		if (sComp.GetBounds().contains(in_window.mapPixelToCoords(sf::Mouse::getPosition(in_window), *m_view)))
		{
			sComp.SetHovered(true);
		}
	}

	//Loop the event queue and handle any input
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

		//Handling mouse releases -- clicking on SelectionComponents 
		else if (auto const* mouseButton = event->getIf<sf::Event::MouseButtonReleased>())
		{
			if (mouseButton->button == sf::Mouse::Button::Left) 
			{
				sf::Vector2f mousePos = in_window.mapPixelToCoords(GetMousePosition(), *m_view);
					
				for (auto& [id, sComp] : in_sComps)
				{
					if (sComp.GetBounds().contains(mousePos))
					{
						//Inform the SelectionComponent it was selected/deselected
						sComp.ToggleSelected();

						//Pass the information along in case of scene-specific behavior not handled by the SelectionComponent itself
						HandleButtonClickedOn(in_window, sComp);
					}
				}
			}
		}

		//Store the scroll wheel value which can be read by other classes
		else if (sf::Event::MouseWheelScrolled const *wheel = event->getIf<sf::Event::MouseWheelScrolled>()) 
		{
			SetMouseScrolled(wheel->delta);
		}
	}
}