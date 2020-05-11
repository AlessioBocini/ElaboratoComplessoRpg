#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animator.h"
#include "AssetManager.h"
#include "Game.h"

using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(624, 624), "rpg game");
    AssetManager assetmanager;
    Event ev;
    //GameManager gamemanager;
    Giocatore player = Giocatore("alessio",Vector2f(0,0));
    Vector2i spriteSize(32, 32);
    player.GetSprite().setTextureRect(IntRect(0, 0, spriteSize.x, spriteSize.y));
    Animator animpg(player.GetSprite());
    auto& animationA = animpg.CreateAnimation("animationA", "../assets/images/pack/Characters/people1.png", seconds(1), true);
    animationA.AddFrames(Vector2i(0, spriteSize.y), spriteSize, 3);
    auto& animationidle = animpg.CreateAnimation("animationS","../assets/images/pack/Characters/people1.png",seconds(1),true);
    animationidle.AddFrames(Vector2i(0, 0), spriteSize, 3);
    auto& animationD = animpg.CreateAnimation("animationD", "../assets/images/pack/Characters/people1.png", seconds(1), true);
    animationD.AddFrames(Vector2i(0, spriteSize.y*2), spriteSize, 3);
    auto& animationW = animpg.CreateAnimation("animationW", "../assets/images/pack/Characters/people1.png", seconds(1), true);
    animationW.AddFrames(Vector2i(0, spriteSize.y * 3), spriteSize, 3);
    animpg.SwitchAnimation("animationS");
    sf::Clock clock;
    while (window.isOpen()) {
        Time deltatime = clock.restart();
        while (window.pollEvent(ev)) {
            if (ev.type == Event::Closed) {
                window.close();
            }


        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            if (animpg.GetCurrentAnimationName() != "animationA")
                animpg.SwitchAnimation("animationA");
            player.Movimento('a');
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            if (animpg.GetCurrentAnimationName() != "animationD")
                animpg.SwitchAnimation("animationD");
            player.Movimento('d');
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if(animpg.GetCurrentAnimationName() != "animationW")
                animpg.SwitchAnimation("animationW");
             player.Movimento('w');
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            if (animpg.GetCurrentAnimationName() != "animationS")
                 animpg.SwitchAnimation("animationS");
            player.Movimento('s');

        }
        
        animpg.update(deltatime);
        window.clear(Color::Blue);
        window.draw(player.GetSprite());
        window.display();
    }

}