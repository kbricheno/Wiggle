#pragma once
#include <SFML/Graphics.hpp>
#include "AssetStore.h"
//u got this <3

/******************
ABSTRACT BASE CLASS
******************/

class Scene {
protected:
	AssetStore* m_assets = nullptr;

public:
	virtual ~Scene() {};

	virtual void SetAssetStore(AssetStore* in_assets) { m_assets = in_assets; }
	virtual void HandleInput(sf::RenderWindow& in_window) = 0;
	virtual void Update(float const in_deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& in_window) = 0;
};