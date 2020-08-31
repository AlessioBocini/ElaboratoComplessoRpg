#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animator.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "Game_State.h"
using namespace sf;

int main() {
   
    GameManager gamemanager;

   while (!gamemanager.getWindow()->isDone()) {
            gamemanager.HandleInput();
          
            gamemanager.CommandConsole();
            
            gamemanager.Update();
            gamemanager.Render();
            sf::sleep(sf::milliseconds(10)); 
            gamemanager.LateUpdate();
    }
   
}