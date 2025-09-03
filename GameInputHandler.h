#pragma once
#include "InputHandler.h"

class GameInputHandler : public InputHandler {
private:
	void HandleButtonClickedOn(sf::RenderWindow& in_window, SelectionComponent* in_buttonClicked) override;

public:

};