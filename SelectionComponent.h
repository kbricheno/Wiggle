#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"

class SelectionComponent : public Component {
private:
	sf::FloatRect const m_selectionBounds;
	bool m_isSelected = false;
	bool m_isHovered = false;

public:
	SelectionComponent(sf::FloatRect in_selectionBounds) : m_selectionBounds(in_selectionBounds) {};

	void Update(GameObject& in_obj) override {};

	sf::FloatRect GetBounds() const { return m_selectionBounds; }
};