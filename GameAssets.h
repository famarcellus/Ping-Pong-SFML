#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Used to conduct several operations within Game
class GameAssets
{
public:


	GameAssets(const int& width = 800, const int& height = 600);	// Creates window

	void SetResolution(sf::RenderWindow* window);
	sf::RenderWindow* getWindow() const;
	int getWidth() const;
	int getHeight() const;

	bool LoadAllAssets();
	bool LoadSprites();
	bool LoadMusic();
	sf::Music& getMusic();

	void Update() const;
	void Draw() const;

private:
	// Screen variables
	int m_ScreenWidth;
	int m_ScreenHeight;
	sf::RenderWindow* window;

	// Background 
	sf::Texture background;
	sf::Sprite screenBG;

	// Music 
	sf::Music jazzMusic;
};
