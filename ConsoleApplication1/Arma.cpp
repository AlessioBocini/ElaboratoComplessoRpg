#include "Arma.h"
#include "EntityManager.h"
int Arma::GetForza() {
	return this->forza;
}
void Arma::SetForza(int const& forza) {
	this->forza = forza;
}


void Arma::SetSprite(sf::Sprite newSprite) {
	this->sprite = newSprite;
}
sf::Sprite& Arma::GetSprite() {
	return this->sprite;
}

Animator* Arma::GetAnimpg()
{
	return &animpg;
}

std::vector<AnimSet> Arma::GetAnimations()
{
	return animations;
}

void Arma::Reset(const std::string& anim) {
	EntityManager* entitymanager = context.entityManager;
	float playerWidth = entitymanager->GetGiocatore()->GetSprite().getGlobalBounds().width;
	float playerHeight = entitymanager->GetGiocatore()->GetSprite().getGlobalBounds().height;
	sf::Vector2f position = entitymanager->GetGiocatore()->GetPosition();
	if (anim=="armaIDLEA") {
		sprite.setPosition(sf::Vector2f(position.x - playerWidth + 4, position.y + playerHeight / 2 + 3));
	}
	else if (anim == "armaIDLED") {
		sprite.setPosition(sf::Vector2f(position.x + playerWidth / 8 - 2, position.y + playerHeight / 2 + 3));
	}
	animpg.SwitchAnimation(anim);
}
void Arma::WeaponPosition(const char& direction) {
	EntityManager* entitymanager = context.entityManager;
	sf::Sprite playerSprite = entitymanager->GetGiocatore()->GetSprite();
	float playerWidth = playerSprite.getGlobalBounds().width;
	float playerHeight = playerSprite.getGlobalBounds().height;
	sf::Vector2f position = entitymanager->GetGiocatore()->GetPosition();
	int currentFrame = animpg.GetCurrentFrame();
	switch (direction)
	{
	case 'A': {
		if (currentFrame == 0) {
			sprite.setPosition(sf::Vector2f(position.x - playerWidth + 6, position.y + playerHeight / 2 + 3));

		}
		else if (currentFrame == 1) {
			sprite.setPosition(sf::Vector2f(position.x - playerWidth + 4, position.y + playerHeight / 2 + 3));
		}
		else if (currentFrame == 2) {
			sprite.setPosition(sf::Vector2f(position.x - playerWidth , position.y + playerHeight / 2 + 3));
		}
		break;
	}
	case 'D':{
		if (currentFrame == 0) {
			sprite.setPosition(sf::Vector2f(position.x + playerWidth / 8 + 3, position.y + playerHeight / 2 + 3));

		}
		else if (currentFrame == 1) {
			sprite.setPosition(sf::Vector2f(position.x + playerWidth / 8 - 2, position.y + playerHeight / 2 + 3));
		}
		else if (currentFrame == 2) {
			sprite.setPosition(sf::Vector2f(position.x + playerWidth / 8 - 4, position.y + playerHeight / 2 + 3));
		}
		break;
	}
	default:
		break;
	}
	
}

Arma::~Arma(){}
