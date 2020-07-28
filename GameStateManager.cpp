#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameAssets.h"
#include "GameStateManager.h"
#include "GameState.h"



using std::array;


GameStateManager::GameStateManager(sf::RenderWindow *window)
{
	m_pCurrentGameState = nullptr;
	gameWindow = window;
}

void GameStateManager::Init()
{
	
	main.SetWindow(gameWindow);
	playMenu.SetWindow(gameWindow);
	settings.SetWindow(gameWindow);
	playing.SetWindow(gameWindow);
	paused.SetWindow(gameWindow);
	
	main.SetGameStateManager(this);
	playMenu.SetGameStateManager(this);
	settings.SetGameStateManager(this);
	settings.SetMusic(jazzMusic);
	playing.SetGameStateManager(this);
	paused.SetGameStateManager(this);
	
	
	m_AllGameStates[0] = &main;
	m_AllGameStates[1] = &playMenu;
	m_AllGameStates[2] = &settings;
	m_AllGameStates[3] = &playing;
	m_AllGameStates[4] = &paused;

	/*
	for (auto i = m_AllGameStates.begin(); i < m_AllGameStates.end(); i++)
	{
		m_pCurrentGameState = *i;
		m_pCurrentGameState->Init();
	}
	*/

	
	for (auto i = 0; i <= 4; ++i)
	{
		m_pCurrentGameState = m_AllGameStates[i];
		m_pCurrentGameState->Init();
	}
	

	
	m_pCurrentGameState = m_AllGameStates[0];
	//m_pCurrentGameState->Init();
	
}

void GameStateManager::ManageEvents(sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		gameWindow->close();
		
		exit(EXIT_SUCCESS);
	}

	if (event.type == sf::Event::KeyPressed)
	{
		m_pCurrentGameState->Input(event);
	}

}


void GameStateManager::ChangeState(const int& i)
{
	m_pCurrentGameState = m_AllGameStates[i];
}

void GameStateManager::Draw()
{
	m_pCurrentGameState->Draw();
}

void GameStateManager::SetMusic(sf::Music& music)
{
	jazzMusic = &music;
}

bool GameStateManager::isPlaying()
{
	if (m_pCurrentGameState == m_AllGameStates[3])
	{
		return true;
	}
	else
	{
		return false;
	}

}

void GameStateManager::Update()
{
	m_pCurrentGameState->Update();
}