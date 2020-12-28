#pragma once
#include "Equipaggiamento.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Animator.h"
#include "SharedContext.h"

using AnimSet = Animator::Animation;
class Arma : public Equipaggiamento {
private:
	int forza;
	sf::Sprite sprite;
	SharedContext& context;
	std::vector<AnimSet> animations;
	Animator animpg;
public:
	

	int GetForza();
	void SetForza(int const& forza);
	void SetSprite(sf::Sprite newSprite);
	sf::Sprite& GetSprite();
	Animator* GetAnimpg();
	std::vector<AnimSet> GetAnimations();
	void Reset(const std::string& anim);
	void WeaponPosition(const char& direction);
	
	Arma(std::string nome, int forza, SharedContext& context) : Equipaggiamento(nome), forza(forza) , animpg(sprite),context(context) {}
	~Arma();
};