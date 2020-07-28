#include "GameState.h"
#include "GameAssets.h"
#include <iostream>
#include "GameStateManager.h"
#include <SFML/Audio.hpp>



class GameAssets;

void GameState::BindWindow(GameAssets& game)
{
	m_ScreenWidth = game.getWidth();
	m_ScreenHeight = game.getHeight();
}

void GameState::SetWindow(sf::RenderWindow* window)
{
	gameWindow = window;
}

void GameState::SetGameStateManager(GameStateManager* gameStateManager)
{
	stateManager = gameStateManager;
}

void GameState::Update()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

MenuState::MenuState()
{

	if (!font.loadFromFile("rivian.otf"))
	{
		std::cerr << "Font did not load successfully, ERROR" << std::endl;
		exit(EXIT_FAILURE);
	}

	selectedItemIndex = 0;


}

void MenuState::Input(sf::Event& event)
{

	if (event.key.code == sf::Keyboard::Up)
	{
		MoveUp();
	}


	if (event.key.code == sf::Keyboard::Down)
	{
		MoveDown();
	}


	if (event.key.code == sf::Keyboard::Enter)
	{
		PressedEnter();
	}

}

void MenuState::BackToDefault()
{
	if (selectedItemIndex != 0) {
		textSelection[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex = 0;
		textSelection[0].setFillColor(sf::Color::Red);
	}
}

void MenuState::MoveUp()
{
	if (selectedItemIndex != 0)
	{
		textSelection[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		textSelection[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MenuState::MoveDown()
{
	if (selectedItemIndex != 2)
	{
		textSelection[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		textSelection[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MenuState::Draw()
{
	for (auto i = textSelection.begin(); i != textSelection.end(); i++)
	{
		gameWindow->draw(*i);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void MainMenu::Init()
{
	title.setString("Ping Pong");
	title.setFont(font);
	title.setCharacterSize(70);
	title.setFillColor(sf::Color::Blue);
	title.setOutlineColor(sf::Color::White);
	title.setOutlineThickness(2.9);
	title.setPosition(250, 0);

	textSelection[0].setFont(font);
	textSelection[0].setFillColor(sf::Color::Red);
	textSelection[0].setString("Play");
	textSelection[0].setPosition(sf::Vector2f(700 / 2, 600 / (MAX_ITEMS + 1) * 1));

	textSelection[1].setFont(font);
	textSelection[1].setFillColor(sf::Color::White);
	textSelection[1].setString("Settings");
	textSelection[1].setPosition(sf::Vector2f(700 / 2, 200));
	

	textSelection[2].setFont(font);
	textSelection[2].setFillColor(sf::Color::White);
	textSelection[2].setString("Exit");
	textSelection[2].setPosition(sf::Vector2f(700 / 2, 250));
	
}

void MainMenu::Draw()
{
	gameWindow->draw(title);

	for (auto i = textSelection.begin(); i != textSelection.end(); i++)
	{
		gameWindow->draw(*i);
	}
}

void MainMenu::PressedEnter()
{
	//BackToDefault();
	switch (selectedItemIndex)
	{
	case 0: 
		BackToDefault();
		stateManager->ChangeState(1);
		break;
	case 1:
		BackToDefault();
		stateManager->ChangeState(2);
		break;
	case 2:
		gameWindow->close();
		exit(EXIT_SUCCESS);
		break;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void PlayMenu::Init()
{
	textSelection[0].setFont(font);
	textSelection[0].setFillColor(sf::Color::Red);
	textSelection[0].setString("SinglePlayer");
	textSelection[0].setPosition(sf::Vector2f(700 / 2, 600 / (MAX_ITEMS + 1) * 1));

	textSelection[1].setFont(font);
	textSelection[1].setFillColor(sf::Color::White);
	textSelection[1].setString("Back to Main Menu");
	textSelection[1].setPosition(sf::Vector2f(700 / 2, 200));
}

void PlayMenu::Draw()
{
	for (auto i = 0; i != 2; i++)
	{
		gameWindow->draw(textSelection[i]);
	}
}

void PlayMenu::PressedEnter()
{
	switch (selectedItemIndex)
	{
	case 0:
		BackToDefault();
		stateManager->ChangeState(3);
		break;
	case 1:
		BackToDefault();
		stateManager->ChangeState(0);
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Settings::Init()
{
	textSelection[0].setFont(font);
	textSelection[0].setFillColor(sf::Color::Red);
	textSelection[0].setString("Music ON/OFF");
	textSelection[0].setPosition(sf::Vector2f(700 / 2, 200));


	textSelection[1].setFont(font);
	textSelection[1].setFillColor(sf::Color::White);
	textSelection[1].setString("Back to Main Menu");
	textSelection[1].setPosition(sf::Vector2f(700 / 2, 250));

}
/*
void Settings::MoveDown()
{
	if (selectedItemIndex != 1)
	{
		textSelection[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		textSelection[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Settings::MoveUp()
{
	if (selectedItemIndex != 0)
	{
		textSelection[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		textSelection[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
*/

void Settings::PressedEnter()
{
	switch (selectedItemIndex)
	{
	case 0:
		if (musicPlaying == true)
		{
			jazz->stop();
		}
		if(musicPlaying == false)
		{
			jazz->play();
		}
		MusicPlaying();
		break;
	case 1:
		BackToDefault();
		stateManager->ChangeState(0);
		break;
	}
}

void Settings::Draw()
{
	for (auto i = 0; i != 2; i++)
	{
		gameWindow->draw(textSelection[i]);
	}
}

void Settings::SetMusic(sf::Music* jazzMusic)
{
	jazz = jazzMusic;
}

void Settings::MusicPlaying()
{
	musicPlaying = !musicPlaying;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Playing::Init()
{

	if (!lineTexture.loadFromFile("line.png"))
	{
		std::cerr << "Line.png did not load successfully, ERROR" << std::endl;
		exit(EXIT_FAILURE);
	}

	lineSprite.setTexture(lineTexture);
	

	if (!font.loadFromFile("rivian.otf"))
	{
		std::cerr << "Font did not load successfully, ERROR" << std::endl;
		exit(EXIT_FAILURE);
	}


	// Sets up Player's paddle
	
	playerPaddle.setSize(sf::Vector2f(30, 100));
	playerPaddle.setOutlineColor(sf::Color::Blue);
	playerPaddle.setOutlineThickness(3);
	playerPaddle.setPosition(745, 150);

	// Sets up Enemy's paddle
	enemyPaddle.setSize(sf::Vector2f(30, 100));
	enemyPaddle.setOutlineColor(sf::Color::Red);
	enemyPaddle.setOutlineThickness(3);
	enemyPaddle.setPosition(100, 50);
	
	

	// Sets up ball
	ball.setRadius(15);
	ball.setOutlineColor(sf::Color::White);
	ball.setOutlineThickness(1);
	ball.setPosition(380, 200);
	srand((unsigned)time(NULL));
	ballDirectionX = rand() % 2;
	ballDirectionY = rand() % 2;
	// Set up mid screen line
	//lineSprite.setPosition(400, 400);

	// Set up Scores
	playerScore.setFont(font);
	enemyScore.setFont(font);

	pScore = 0;
	eScore = 0;

	playerScore.setFont(font);
	playerScore.setFillColor(sf::Color::White);
	playerScore.setString(std::to_string(pScore));
	playerScore.setPosition(600, 0);

	playerName.setFont(font);
	playerName.setString("Player");
	playerName.setPosition(550, 50);
	playerName.setOutlineColor(sf::Color::Blue);
	playerName.setOutlineThickness(1);


	enemyScore.setFont(font);
	enemyScore.setFillColor(sf::Color::White);
	enemyScore.setString(std::to_string(eScore));
	enemyScore.setPosition(200, 0);

	enemyName.setFont(font);
	enemyName.setString("AI");
	enemyName.setPosition(190, 50);
	enemyName.setOutlineColor(sf::Color::Red);
	enemyName.setOutlineThickness(1);
}

void Playing::Draw()
{
	gameWindow->draw(playerPaddle);
	gameWindow->draw(enemyPaddle);
	gameWindow->draw(ball);

	gameWindow->draw(playerScore);
	gameWindow->draw(playerName);

	gameWindow->draw(enemyScore);
	gameWindow->draw(enemyName);

}

void Playing::Update()
{
	
	BallSpawnDirection();

	
	if (enemyPaddle.getPosition().y + 15 > ball.getPosition().y)
	{
		enemyPaddle.move(0, -0.03);
	}

	if(enemyPaddle.getPosition().y - 15 < ball.getPosition().y)
	{
		enemyPaddle.move(0, 0.03);
	}
	

	Movement();

}

void Playing::BallSpawnDirection()
{
	if (spawning == true)
	{
		if (ballDirectionX == 0)
		{
			if (ballDirectionY == 0)
			{
				ballVelocityX = -0.03;
				ballVelocityY = -0.02;
				//ball.move(-0.02, -0.02);
			}
			else
			{
				ballVelocityX = -0.03;
				ballVelocityY = 0.02;
				//ball.move(-0.02, 0.02);
			}
		}

		if (ballDirectionX == 1)
		{
			if (ballDirectionY == 0)
			{
				ballVelocityX = 0.03;
				ballVelocityY = -0.02;
				//ball.move(0.02, -0.02);
			}
			else
			{
				ballVelocityX = 0.03;
				ballVelocityY = 0.02;
				//ball.move(0.02, 0.02);
			}
		}
	}


	if (ball.getPosition().y < 0)
	{
		spawning = false;
		ballVelocityY = -1 * (ballVelocityY);
		//ball.move(0.13, 3);
	}

	if (ball.getPosition().y - 15 > 555)
	{
		spawning = false;
		ballVelocityY = -1 * (ballVelocityY);
		//ball.move(13, 21);
	}
	

	if (enemyPaddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
	{
		ballVelocityX = -(ballVelocityX);
	}

	if (playerPaddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
	{
		ballVelocityX = -(ballVelocityX);
	}


	ball.move(ballVelocityX, ballVelocityY);

	if (ball.getPosition().x < 0)
	{
		stateManager->ChangeState
	}
}

void Playing::Input(sf::Event& event)
{
}

void Playing::Movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		playerPaddle.move(0, -0.03);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		playerPaddle.move(0, 0.03);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameFinished::Init()
{
	title.setString("PAUSED");
	title.setFont(font);
	title.setCharacterSize(70);
	title.setFillColor(sf::Color::Blue);
	title.setOutlineColor(sf::Color::White);
	title.setOutlineThickness(2.9);
	title.setPosition(250, 0);

	textSelection[0].setFont(font);
	textSelection[0].setFillColor(sf::Color::Red);
	textSelection[0].setString("Resume");
	textSelection[0].setPosition(sf::Vector2f(700 / 2, 600 / (MAX_ITEMS + 1) * 1));

	textSelection[1].setFont(font);
	textSelection[1].setFillColor(sf::Color::White);
	textSelection[1].setString("Back to Main Menu");
	textSelection[1].setPosition(sf::Vector2f(700 / 2, 200));

}

void Paused::Draw()
{
	gameWindow->draw(title);

	for (auto i = 0; i != 2; i++)
	{
		gameWindow->draw(textSelection[i]);
	}
}

void Paused::MoveDown()
{
	if (selectedItemIndex != 1)
	{
		textSelection[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		textSelection[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Paused::MoveUp()
{
	if (selectedItemIndex != 0)
	{
		textSelection[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		textSelection[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Paused::PressedEnter()
{
	switch (selectedItemIndex)
	{
	case 0:
		stateManager->ChangeState(3);
		break;
	case 1:
		BackToDefault();
		stateManager->ChangeState(0);
		break;
	}
}