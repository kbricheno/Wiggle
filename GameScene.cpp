#include "GameScene.h"
#include <iostream>

GameScene::GameScene(sf::Vector2u const in_windowSize) 
{
	//Set up view size and position (size = (arbitrary value * tile size) as a ratio of the size of the window)
	m_gameView.setSize({ (float)m_TILE_SIZE * m_viewScroll, in_windowSize.y * (m_TILE_SIZE * m_viewScroll / (float)in_windowSize.x)});
	m_gameView.setCenter(m_map.GetMapVertices().getBounds().size / 2.f);

	//setup input handler
	

	//setup map
	m_map.PrintMap(); //ensure the map was generated correctly
	//spawn gameobjects & components
}

void GameScene::HandleInput(sf::RenderWindow& in_window) 
{
	UpdateView(in_window);

	//inputcomponents.HandleInput(in_window);
}

void GameScene::Update(float const in_deltaTime)
{
	//behaviourcomponents.Update(in_deltaTime);
	//physicscomponents.Update(in_deltaTime);
	//audiocomponents.Update(in_deltaTime);
}

//Move and zoom the view
void GameScene::UpdateView(sf::RenderWindow& in_window)
{
	//Get the mouse position relative to the window (TODO: receive input from handler)
	sf::Vector2i mousePos = sf::Mouse::getPosition(in_window);

	//Only move and/or zoom the view if the mouse is within the window
	if (in_window.getViewport(m_gameView).contains(mousePos)) 
	{
		//Panning the view
		
		//Set a direction vector for moving the view and obtain the view's current position
		sf::Vector2f moveDir = { 0,0 };
		sf::Vector2f centerPos = m_gameView.getCenter();

		//If the mouse is within a short distance of one or more sides of the screen, update the direction vector
		if (mousePos.x > in_window.getSize().x - m_VIEW_MOVE_BOUNDS) moveDir.x += 1; 
		if (mousePos.y > in_window.getSize().y - m_VIEW_MOVE_BOUNDS) moveDir.y += 1; 
		if (mousePos.x < m_VIEW_MOVE_BOUNDS) moveDir.x -= 1; 
		if (mousePos.y < m_VIEW_MOVE_BOUNDS) moveDir.y -= 1; 

		//Normalize the direction vector, multiply it by the view's move speed (TODO: * deltaTime), then add it to the view's position
		if (moveDir != sf::Vector2f({ 0,0 })) centerPos += moveDir.normalized() * m_VIEW_MOVE_SPEED;

		//Ensure the view cannot move outside of the bounds of the map
		sf::Vector2f minBounds = m_map.GetMapVertices().getBounds().position + m_gameView.getSize() / 2.f;
		sf::Vector2f maxBounds = m_map.GetMapVertices().getBounds().size - m_gameView.getSize() / 2.f;
		if (centerPos.x < minBounds.x) centerPos.x = minBounds.x;
		if (centerPos.y < minBounds.y) centerPos.y = minBounds.y;
		if (centerPos.x > maxBounds.x) centerPos.x = maxBounds.x;
		if (centerPos.y > maxBounds.y) centerPos.y = maxBounds.y;

		//Set the view's new position
		m_gameView.setCenter(centerPos);


		//Zooming the view

		//When arrow keys are pressed (TODO: switch to scroll wheel, receive input from handler), alter the view scroll
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) m_viewScroll -= m_VIEW_SCROLL_INCREMENT;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) m_viewScroll += m_VIEW_SCROLL_INCREMENT;

		//Clamp the view size to its minimum and maximum bounds
		m_viewScroll = std::clamp(m_viewScroll, m_VIEW_SCROLL_BOUNDS.x, m_VIEW_SCROLL_BOUNDS.y);

		//Set the view's new size (as a ratio of the size of the window)
		m_gameView.setSize({ (float)m_TILE_SIZE * m_viewScroll, in_window.getSize().y * (m_TILE_SIZE * m_viewScroll / (float)in_window.getSize().x) });
	}
}

void GameScene::Draw(sf::RenderWindow& in_window)
{
	in_window.setView(m_gameView);

	//visualcomponents.Draw(in_window);

	sf::Texture bgTex = m_assets->GetBitmap("grass");
	in_window.draw(m_map.GetMapVertices(), &bgTex);
}