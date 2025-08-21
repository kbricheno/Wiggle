#pragma once
#include <SFML/Graphics.hpp>
//u got this <3

/********
INTERFACE
********/
class Scene {
public:
	virtual ~Scene() {};

	virtual void HandleInput(sf::RenderWindow& in_window) = 0;
	virtual void Update(float const in_deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& in_window) = 0;
};