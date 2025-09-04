#pragma once
#include "InputHandler.h"

class GameInputHandler : public InputHandler {
private:
	void HandleButtonClickedOn(sf::RenderWindow& in_window, SelectionComponent in_sCompClicked) override;
	void HandleMouseScrolled(sf::RenderWindow& in_window, bool in_isScrollingUp) override;

public:
	GameInputHandler() : InputHandler(nullptr, nullptr, {sf::View()}) {}
	GameInputHandler(Scene* in_scene, SceneManager* in_sceneManager, std::vector<sf::View> in_views) : InputHandler(in_scene, in_sceneManager, in_views) {}
};