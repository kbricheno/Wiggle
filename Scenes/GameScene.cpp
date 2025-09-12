#include <iostream>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "GameScene.h"
#include "../AssetStore.h"

GameScene::GameScene(sf::RenderWindow const& in_window)
{
	//setup map
	m_map.PrintMap(); //ensure the map was generated correctly

	//spawn gameobjects & components
	//Map GameObjects
	for (int i = 0; i < m_map.GetMapVertices().getVertexCount(); i+=6)
	{
		GameObject mapTile;
		SelectionComponent sComp(sf::FloatRect(m_map.GetMapVertices()[i].position, sf::Vector2f(m_TILE_SIZE, m_TILE_SIZE)));
		m_gameObjects.insert({ currentId, mapTile });
		m_selectionComponents.insert({ currentId, sComp });

		currentId++;
	}
		
	//Set up view size and position (size = (arbitrary value * tile size) as a ratio of the size of the window)
	m_gameView.setSize({ (float)m_TILE_SIZE * m_currentViewZoom, in_window.getSize().y * (m_TILE_SIZE * m_currentViewZoom / (float)in_window.getSize().x)});
	m_gameView.setCenter(m_map.GetMapVertices().getBounds().size / 2.f);
}

void GameScene::Initialize(AssetStore* in_assets, SceneManager* in_sceneManager)
{
	Scene::Initialize(in_assets, in_sceneManager);

	m_inputHandler.Initialize(this, m_sceneManager, &m_gameView);
}

#pragma region Game Loop

void GameScene::HandleInput(sf::RenderWindow& in_window) 
{
	m_inputHandler.HandleInput(in_window, m_selectionComponents);
}

void GameScene::Update(sf::RenderWindow& in_window, float const in_deltaTime)
{
	//behaviourcomponents.Update(in_deltaTime);
	//physicscomponents.Update(in_deltaTime);
	//audiocomponents.Update(in_deltaTime);

	//Update the View's position and size based on input received
	PanView(in_window, in_deltaTime);
	ZoomView(in_window, in_deltaTime);
	m_mouseWheelDelta = 0; //Reset the delta each frame to prevent scrolling when no input is given
}

void GameScene::Draw(sf::RenderWindow& in_window)
{
	in_window.setView(m_gameView);

	//visualcomponents.Draw(in_window);

	sf::Texture bgTex = m_assets->GetBitmap("grass");
	in_window.draw(m_map.GetMapVertices(), &bgTex);

	//Temporarily draw shapes to visualise the SelectionComponents
	for (auto& [id, sComp] : m_selectionComponents)
	{
		sf::RectangleShape shape;
		shape.setPosition(sComp.GetBounds().position);
		shape.setSize(sComp.GetBounds().size);
		shape.setOutlineThickness(2.f);
		if (sComp.IsSelected()) shape.setOutlineColor(sf::Color::Cyan);
		else if (sComp.IsHovered()) shape.setOutlineColor(sf::Color::Blue);
		else shape.setOutlineColor(sf::Color::Red);
		shape.setFillColor(sf::Color::Transparent);

		in_window.draw(shape);
	}

	sf::RectangleShape mouseFollow;
	mouseFollow.setPosition(in_window.mapPixelToCoords(sf::Mouse::getPosition(in_window), m_gameView));
	mouseFollow.setSize({ 25, 25 });
	mouseFollow.setFillColor(sf::Color::Yellow);
	in_window.draw(mouseFollow);
}
#pragma endregion

#pragma region View

//Zoom the view
void GameScene::ZoomView(sf::RenderWindow const& in_window, float const in_deltaTime)
{
	//When mouse wheel is scrolled, alter the view scroll
	if (m_mouseWheelDelta < 0) m_currentViewZoom += m_VIEW_SCROLL_INCREMENT * in_deltaTime;
	else if (m_mouseWheelDelta > 0) m_currentViewZoom -= m_VIEW_SCROLL_INCREMENT * in_deltaTime;

	//Clamp the view size to its minimum and maximum bounds
	m_currentViewZoom = std::clamp(m_currentViewZoom, m_VIEW_SCROLL_BOUNDS.x, m_VIEW_SCROLL_BOUNDS.y);

	//Set the view's new size (as a ratio of the size of the window)
	m_gameView.setSize({ (float)m_TILE_SIZE * m_currentViewZoom, in_window.getSize().y * (m_TILE_SIZE * m_currentViewZoom / (float)in_window.getSize().x) });
}

//Move the view
void GameScene::PanView(sf::RenderWindow const& in_window, float const in_deltaTime) 
{
	//Only move and/or zoom the view if the mouse is within the window
	if (in_window.getViewport(m_gameView).contains(m_mousePosInWindow))
	{
		//Set a direction vector for moving the view and obtain the view's current position
		sf::Vector2f moveDir = { 0,0 };
		sf::Vector2f centerPos = m_gameView.getCenter();

		//If the mouse is within a short distance of one or more sides of the screen, update the direction vector
		if (m_mousePosInWindow.x > (int)in_window.getSize().x - m_VIEW_MOVE_BOUNDS) moveDir.x += 1;
		if (m_mousePosInWindow.y > (int)in_window.getSize().y - m_VIEW_MOVE_BOUNDS) moveDir.y += 1;
		if (m_mousePosInWindow.x < m_VIEW_MOVE_BOUNDS) moveDir.x -= 1;
		if (m_mousePosInWindow.y < m_VIEW_MOVE_BOUNDS) moveDir.y -= 1;

		//Normalize the direction vector, multiply it by the view's move speed, then add it to the view's position
		if (moveDir != sf::Vector2f({ 0,0 })) centerPos += moveDir.normalized() * m_VIEW_MOVE_SPEED * in_deltaTime;

		//Ensure the view cannot move outside of the bounds of the map
		sf::Vector2f minBounds = m_map.GetMapVertices().getBounds().position + m_gameView.getSize() / 2.f;
		sf::Vector2f maxBounds = m_map.GetMapVertices().getBounds().size - m_gameView.getSize() / 2.f;
		if (centerPos.x < minBounds.x) centerPos.x = minBounds.x;
		if (centerPos.y < minBounds.y) centerPos.y = minBounds.y;
		if (centerPos.x > maxBounds.x) centerPos.x = maxBounds.x;
		if (centerPos.y > maxBounds.y) centerPos.y = maxBounds.y;

		//Set the view's new position
		m_gameView.setCenter(centerPos);
	}
}
#pragma endregion