#include "GameEngine.h"

//Define the static bool that allows only one instance of GameEngine to exist
bool GameEngine::m_isInstantiated = false;

//Construct the GameEngine instance, ensuring only one instance can be created
GameEngine::GameEngine() 
{
	assert(!m_isInstantiated);
	m_isInstantiated = true;

	m_window.setKeyRepeatEnabled(false); //turn off key repeat to prevent multiple key press events being triggered by holding a key down
}

//Should the singular GameEngine instance be destroyed, another one can now be created
GameEngine::~GameEngine() 
{
	m_isInstantiated = false;
}

void GameEngine::Run() 
{
	//run the game while the window is open
	while (m_window.isOpen()) 
	{
		m_deltaTime = m_clock.restart().asSeconds();

		HandleInput();
		Update();
		Draw();
	}
}

void GameEngine::HandleInput() 
{
	m_sceneManager.HandleInput(m_window);
}

void GameEngine::Update()
{
	m_sceneManager.Update(m_deltaTime);
}

void GameEngine::Draw()
{
	m_window.clear(sf::Color::Black);
	m_sceneManager.Draw(m_window);
	m_window.display();
}