#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Animator.h"
#include "AssetManager.h"
#include "Game.h"


using namespace sf;

/*
int main()
{
    sf::RenderWindow window(sf::VideoMode(128*3, 221*2), "SFML works!");
   /* sf::Texture texture;
    texture.loadFromFile("../myTexture.jpg");
    texture.setRepeated(true);*/
    /*sf::RectangleShape rect(sf::Vector2f(128*3, 221*2));
    rect.setTextureRect(IntRect(0, 0, 128, 221));
    rect.setTexture(&texture);
    
   // texture.setSmooth(true);
   /* ConvexShape conv(5);
    conv.setPoint(0, Vector2f(0, 0));
    conv.setPoint(1, Vector2f(200, 0));
    conv.setPoint(2, Vector2f(180, 120));
    conv.setPoint(3, Vector2f(100, 200));
    conv.setPoint(4, Vector2f(20, 120));
    conv.setTexture(&texture);*/

    /*conv.setOutlineThickness(2);
    conv.setOutlineColor(Color::Red);*/
  /*  AssetManager manager;
    Vector2i spriteSize(16, 16);
    Texture texture = AssetManager::GetTexture("../assets/sheet.png");
    Sprite sprite = Sprite(texture);
    sprite.setTextureRect(IntRect(0, 0, spriteSize.x, spriteSize.y));
    int framesNum = 4; //3 frames 
    float animationduration = 3; //1 sec
    
    Clock clock;
    Time elapsedTime;
    int count = 0; 
    while (window.isOpen())
    {
        Time deltatime = clock.restart();
        Event event;
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
        }
        elapsedTime += deltatime;
        float timeAsSeconds = elapsedTime.asSeconds();
        int animframe = static_cast<int>((timeAsSeconds / animationduration) * framesNum) % framesNum;
        
        
         sprite.setTextureRect(IntRect(animframe * spriteSize.x, 0, spriteSize.x, spriteSize.y)); 
       
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}*/
/*
int main() {
    sf::RenderWindow window(sf::VideoMode(624 , 624), "SFML works!");

    //
    auto wSize = window.getSize();
    //View view(FloatRect(0, 0, wSize.x, wSize.y));
    View view1(Vector2f(0, 0), Vector2f(wSize.x, wSize.y));
    //view.setCenter(Vector2f(0, 0));
    view1.setViewport(FloatRect(0, 0, 0.5f, 0.5f));
    View view2(Vector2f(0, 0), Vector2f(wSize.x, wSize.y));
    view2.setViewport(FloatRect(0.5f, 0, 0.5f, 0.5f));
    View view4(Vector2f(0, 0), Vector2f(wSize.x, wSize.y));
    view2.setRotation(50);
    view4.setViewport(FloatRect(0.5f, 0.5f, 0.5f, 0.5f));
    view4.zoom(0.5);
    View view3(Vector2f(0, 0), Vector2f(wSize.x, wSize.y));
    view3.setViewport(FloatRect(0, 0.5f, 0.5f, 0.5f));
    window.setView(view1);
    sf::Vector2i spriteSize(32, 32);
    AssetManager assetmanager;
    std::vector<View> viewList;
    viewList.push_back(view1);
    viewList.push_back(view2);
    viewList.push_back(view3);
    viewList.push_back(view4);
    Sprite sprite = Sprite();
    Animator animator(sprite);

    sf::Text text("look at meee!", AssetManager::GetFont("../assets/OpenSans-Light.ttf"));
    Sound sound(AssetManager::GetSoundBuffer("../assets/sounds/punch.ogg"));
    view1.setCenter(sprite.getPosition());
    auto& animationidle = animator.CreateAnimation("idle", "../assets/images/cc.png", seconds(1), true);
    animationidle.AddFrames(Vector2i(0, 0), spriteSize, 8);

    auto& animationidle2 = animator.CreateAnimation("idle2", "../assets/images/ros1.png", seconds(1), true);
   // animationidle2.AddFrames(Vector2i(0, 0), spriteSize1, 8);
    Music music;
    if (!music.openFromFile("../assets/music/comatoes.ogg"))
        return -1;
    music.setVolume(20);
    music.play();
    music.setLoop(true);
    animationidle2.AddFrames(Vector2i(0, 0), spriteSize, 8);

    auto& animationidle3 = animator.CreateAnimation("idle3", "../assets/images/ros2.png", seconds(1), true);
    animationidle3.AddFrames(Vector2i(0, 0), spriteSize, 8);
    sf::Clock clock;
    
    auto& texture = AssetManager::GetTexture("../assets/images/cel2.png");
    
    Vector2f spritesize = Vector2f(32, 32);
    Sprite bor1(texture);
    bor1.setOrigin(spritesize * 0.5f);
    bor1.setPosition(Vector2f(-80, -80));


    Sprite bor2(texture);
    bor2.setOrigin(spritesize * 0.5f);
    bor2.setPosition(Vector2f(80, -80));
    Sprite bor3(texture);
    bor3.setOrigin(spritesize * 0.5f);
    bor3.setPosition(Vector2f(80, 80));
    Sprite bor4(texture);
    bor4.setOrigin(spritesize * 0.5f);
    bor4.setPosition(Vector2f(-80, 80));
    /*RenderTexture rTexture;
    auto wSize = window.getSize();
    rTexture.create(wSize.x, wSize.y);
    Sprite ppsprite(rTexture.getTexture());
    auto shader = AssetManager::GetShader("vertShader.vert", "pixelationShader.frag");
    shader->setParameter("uTexture", rTexture.getTexture());
    shader->setParameter("uTextureSize", static_cast<sf::Vector2f>(rTexture.getSize()));
    shader->setParameter("uPixelSize", 8);*/
/*
    sprite.setTextureRect(IntRect(0, 0, spriteSize.x, spriteSize.y));
    int pressed = 0;
    while (window.isOpen()) {
       Time deltatime = clock.restart();
       Event event;
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::A) {
                    animator.SwitchAnimation("idle2");
                    pressed = 1;
                }
                else if (event.key.code == Keyboard::D) {
                    animator.SwitchAnimation("idle");
                    pressed = 2;
                }
                else if (event.key.code == Keyboard::S) {
                    animator.SwitchAnimation("idle3");
                    pressed = 3;
                }
                else if (event.key.code == Keyboard::W) {
                    animator.SwitchAnimation("idle4");
                    pressed = 4;
                }
                else if (event.key.code == Keyboard::F) {
                    sound.play();
                }
            }
            if (event.type == Event::KeyReleased)
                pressed = 0;

            if (event.type == Event::MouseButtonPressed) {
                Vector2f scenecoords = window.mapPixelToCoords(
                    Vector2i(event.mouseButton.x, event.mouseButton.y)
                    );
                sprite.setPosition(scenecoords);
                    
            }
        }

        /*rTexture.clear();
        {

        }
        rTexture.display();*/



/*
        if (pressed == 1) {
            sprite.move(-0.2, 0);
        }
        else if (pressed == 2) {
            sprite.move(0.2, 0);
        }
        else if (pressed == 3) {
            sprite.move(0, 0.2);
        }
        else if (pressed == 4) {
            sprite.move(0, -0.2);
        }

        animator.update(deltatime);
        window.clear(Color::Black);
       for (auto it = viewList.begin(); it != viewList.end(); it++) {
            window.setView(*it);
            
            window.draw(bor1);
            window.draw(bor2);
            window.draw(bor3);
            window.draw(bor4);
         
           
           
        }
       /*
        {
            window.draw(ppsprite,shader);
        }*//*
        window.display();
    }
}
*/

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