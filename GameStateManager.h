#pragma once
#include <array>
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*
class GameState;
class MainMenu;
class PlayMenu;
class Settings;
class SinglePlayer;
class Multiplayer;
*/

class GameStateManager
{
public:
	GameStateManager(sf::RenderWindow* window);
	void Init();

	void ManageEvents(sf::Event& event);
	void ChangeState(const int& i);
	void Draw();
	void SetMusic(sf::Music& music);
	bool isPlaying();
	void Update();


private:
	class GameState *m_pCurrentGameState;
	std::array<GameState*, 6> m_AllGameStates = {};

	MainMenu main;
	PlayMenu playMenu;
	Settings settings;

	Playing playing;
	Paused paused;

	sf::RenderWindow* gameWindow;
	sf::Music* jazzMusic;
};

