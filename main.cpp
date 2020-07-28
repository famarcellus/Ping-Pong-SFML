#include <iostream>
#include <string>
#include <array>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameAssets.h"
#include "GameStateManager.h"
#include "GameState.h"





int main()
{ 
    GameAssets Game;

    if (!Game.LoadAllAssets())
    {
        return EXIT_FAILURE;
    }
    
    GameStateManager stateMachine(Game.getWindow());
    
    stateMachine.SetMusic(Game.getMusic());
    stateMachine.Init();    // calls Init() in each state
    

    
    // Game loop
    while (Game.getWindow()->isOpen())
    {
       
        sf::Event event;
        if (!stateMachine.isPlaying())
        {
            while (Game.getWindow()->pollEvent(event))
            {
                // Manages Events and Input
                stateMachine.ManageEvents(event);
            }
        }
      
        // Only update if game is in Play State
        if (stateMachine.isPlaying())
        {
            stateMachine.Update();
        }

        Game.getWindow()->clear();

        stateMachine.Draw();

        Game.getWindow()->display();        
    }
    
        
    return 0;
}