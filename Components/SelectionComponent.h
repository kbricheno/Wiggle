#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "Component.h"

class GameObject;

class SelectionComponent : public Component {
private:
	sf::FloatRect const m_selectionBounds;
	bool m_isSelected = false;
	bool m_isHovered = false;

public:
	SelectionComponent(sf::FloatRect in_selectionBounds) : m_selectionBounds(in_selectionBounds) {}

	void Update(GameObject& in_obj) override {}

	sf::FloatRect GetBounds() const { return m_selectionBounds; }

	bool IsHovered() const { return m_isHovered; }
	bool IsSelected() const { return m_isSelected; }
	void SetHovered(bool in_hovered) { m_isHovered = in_hovered; }
	void ToggleSelected() { m_isSelected = !m_isSelected; }
};