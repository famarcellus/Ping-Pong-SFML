#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "GameAssets.h"



GameAssets::GameAssets(const int &width,const int &height) :
	m_ScreenWidth(width),
	m_ScreenHeight(height)
{
	window = new sf::RenderWindow(sf::VideoMode(m_ScreenWidth, m_ScreenHeight), "Ping Pong");
}

sf::RenderWindow* GameAssets::getWindow() const
{
	return window;
}

int GameAssets::getWidth() const
{
	return m_ScreenWidth;
}

int GameAssets::getHeight() const
{
	return m_ScreenHeight;
}

bool GameAssets::LoadAllAssets()
{
	if (!LoadSprites() || !LoadMusic())
	{
		return false;
	}

	return true;
}

bool GameAssets::LoadSprites()
{
	if (!background.loadFromFile("blackbg.jpg"))
	{
		std::cerr << "Background did not load succesfully, ERROR" << std::endl;
		return false;
	}

	screenBG.setTexture(background);

	return true;
}

bool GameAssets::LoadMusic()
{
	if (!jazzMusic.openFromFile("jazzMusic.wav"))
	{
		std::cerr << "Music did not load successfuly, ERROR" << std::endl;
		return false;
	}
	jazzMusic.setVolume(30);
	jazzMusic.setLoop(true);
	jazzMusic.play();

	return true;
}


sf::Music& GameAssets::getMusic()
{
	return jazzMusic;
}



void GameAssets::Update() const
{
	Draw();
}

void GameAssets::Draw() const
{
	window->draw(screenBG);
}

