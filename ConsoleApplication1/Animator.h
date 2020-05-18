
#ifndef ANIMATOR_H
    #define ANIMATOR_H




#include <list>
#include <SFML\System\Time.hpp>
#include <vector>
#include <string>

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics.hpp>


class Animator {
public:
    struct Animation {
        std::string m_Name;
        std::string m_TextureName;
        std::vector<sf::IntRect> m_frames;
        sf::Time m_duration;
        bool m_looping;
        Animation(std::string const& name, std::string const& textureName, sf::Time const& duration, bool looping)
            :m_Name(name), m_TextureName(textureName), m_duration(duration), m_looping(looping) {}
        
        void AddFrames(sf::Vector2i const& startFrom, sf::Vector2i const& frameSize, unsigned int frames) {
            sf::Vector2i current = startFrom;
            for (unsigned int i = 0; i < frames; i++) {
                m_frames.push_back(sf::IntRect(current.x, current.y, frameSize.x, frameSize.y));
                current.x += frameSize.x;
            }
        }
    };
    Animator(sf::Sprite& sprite);
    Animator::Animation& CreateAnimation(std::string const& name, std::string const& textureName, sf::Time const& duration, bool loop = false);
    void update(sf::Time const& dt);
    bool SwitchAnimation(std::string const& name);
    std::string GetCurrentAnimationName() const;
private:
    Animator::Animation* FindAnimation(std::string const& name);
    void SwitchAnimation(Animator::Animation* animation);
    sf::Sprite& m_sprite;
    sf::Time m_currenttime;
    std::list<Animator::Animation> m_animations;
    Animator::Animation* m_currentAnimation;
};

#endif