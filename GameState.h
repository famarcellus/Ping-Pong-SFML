#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <time.h>


constexpr auto MAX_ITEMS = 3;

class GameStateManager;
class GameAssets;

class GameState
{
public:

	virtual void Init() = 0;                                                   

	virtual void Draw() = 0;

	virtual void Input(sf::Event& event) = 0;

	virtual void Update();

	void BindWindow(GameAssets& game);

	void SetWindow(sf::RenderWindow* window);
	
	void SetGameStateManager(GameStateManager* gameStateManager);



protected:
	sf::RenderWindow* gameWindow;
	int m_ScreenWidth;
	int m_ScreenHeight;

	GameStateManager* stateManager;
	
	sf::Music* jazz;

};

class MenuState : public GameState
{
public:
	MenuState();
	virtual void Input(sf::Event& event);

	virtual void MoveUp();
	virtual void MoveDown();
	virtual void PressedEnter() = 0;
	virtual void BackToDefault();
	virtual void Draw();

protected:
	std::array<sf::Text, MAX_ITEMS> textSelection;
	int selectedItemIndex;
	sf::Font font;
};


class MainMenu : public MenuState
{
public:
	void virtual Init();
	void virtual Draw();
	void virtual PressedEnter();

private:
	sf::Text title;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PlayMenu : public MenuState
{
public:
	void virtual Init();
	void virtual Draw();
	void virtual PressedEnter();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Settings : public MenuState
{
public:
	void virtual Init();
	void SetMusic(sf::Music* jazzMusic);

	//void MoveUp();
	//void MoveDown();
	void virtual PressedEnter();

	void Draw();
	void MusicPlaying();

private:
	bool musicPlaying = true;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Playing : public GameState
{
	
public:
	virtual void Init();

	virtual void Update();

	virtual void Draw();

	virtual void Input(sf::Event& event);

	void Movement();

	void BallSpawnDirection();


private:

	sf::RectangleShape playerPaddle;
	sf::RectangleShape enemyPaddle;
	

	sf::CircleShape ball;
	sf::Texture lineTexture;
	sf::Sprite lineSprite;
	sf::Font font;

	sf::Text playerScore;
	sf::Text playerName;
	sf::Text enemyScore;
	sf::Text enemyName;

	int ballDirectionX;
	int ballDirectionY;

	int pScore;
	int eScore;

	bool spawning = true;

	double ballVelocityX;
	double ballVelocityY;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameFinished : public MenuState
{
public:
	void virtual Init();

	void MoveUp();
	void MoveDown();
	void virtual PressedEnter();

	void Draw();
	

private:
	sf::Text title;
};

