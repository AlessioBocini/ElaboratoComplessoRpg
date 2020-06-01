#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animator.h"
#include "AssetManager.h"
#include "GameManager.h"


using namespace sf;

int main() {
   
    GameManager gamemanager;

    auto& animationA = gamemanager.animpg.CreateAnimation("animationA", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
    animationA.AddFrames(sf::Vector2i(0, gamemanager.spriteSize.y), gamemanager.spriteSize, 3);
    auto& animationidle = gamemanager.animpg.CreateAnimation("animationS", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
    animationidle.AddFrames(sf::Vector2i(0, 0), gamemanager.spriteSize, 3);
    auto& animationD = gamemanager.animpg.CreateAnimation("animationD", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
    animationD.AddFrames(sf::Vector2i(0, gamemanager.spriteSize.y * 2), gamemanager.spriteSize, 3);
    auto& animationW = gamemanager.animpg.CreateAnimation("animationW", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
    animationW.AddFrames(sf::Vector2i(0, gamemanager.spriteSize.y * 3), gamemanager.spriteSize, 3);


   
   while (!gamemanager.getWindow()->isDone()) {

         gamemanager.HandleInput();
        
        gamemanager.Update();
        gamemanager.Render();
        sf::sleep(sf::milliseconds(10)); 
        gamemanager.RestartClock();
    }
   
}