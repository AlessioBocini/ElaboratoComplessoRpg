
#include "Animator.h"
#include "AssetManager.h"
#include <iostream>
#include "CustomException.h"

Animator::Animator(sf::Sprite& sprite) :m_sprite(sprite), m_currenttime(), m_currentAnimation(nullptr) {}

Animator::Animation& Animator::CreateAnimation(std::string const& name, std::string const& texturename, sf::Time const& duration, bool loop) {
    m_animations.push_back(Animator::Animation(name, texturename, duration, loop));
    if (m_currentAnimation == nullptr)
        SwitchAnimation(&(m_animations.back()));

    return m_animations.back();
}
void Animator::SwitchAnimation(Animator::Animation* animation) {

    try {
        sf::Texture& texture = AssetManager::GetTexture(animation->m_TextureName);
        if (animation != nullptr)
            this->m_sprite.setTexture(texture);
        m_currentAnimation = animation;
        m_currenttime = sf::Time::Zero;//resetta il tempo
    }
    catch (TextureException e) {
        std::cout << e.what() << std::endl;
    }
}
bool Animator::SwitchAnimation(std::string const& name) {
    auto animation = FindAnimation(name);
    if (animation != nullptr) {
        SwitchAnimation(animation);
        return true;
    }
    return false;
}
Animator::Animation* Animator::FindAnimation(std::string const& name) {
    for (auto it = m_animations.begin(); it != m_animations.end(); it++) {
        if (it->m_Name == name)
            return &*it;
    }
    return nullptr;
}
std::string Animator::GetCurrentAnimationName() const {
    if (m_currentAnimation != nullptr) {
        return m_currentAnimation->m_Name;
    }
    return "";
}

void Animator::update(sf::Time const& dt) {
    if (m_currentAnimation == nullptr)
        return;
    m_currenttime += dt;
    

    m_sprite.setTextureRect(m_currentAnimation->m_frames[GetCurrentFrame(dt)]);
}

int Animator::GetCurrentFrame(sf::Time const& dt) {
    float scaledtime = (m_currenttime.asSeconds() / m_currentAnimation->m_duration.asSeconds());
    int numframes = m_currentAnimation->m_frames.size();
    int currentframe = static_cast<int>(scaledtime * numframes);
    if (m_currentAnimation->m_looping)
        currentframe %= numframes;
    else if (currentframe >= numframes)//se è più grande 
        currentframe = numframes - 1;   //setta l'ultimo

    return currentframe;
}
int Animator::GetCurrentFrame() {
   return GetCurrentFrame(sf::Time::Zero);
}