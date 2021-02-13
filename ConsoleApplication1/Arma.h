#pragma once
#include "Equipaggiamento.h"

class Arma : public Equipaggiamento {
private:
	int forza;
	sf::Sprite sprite;
	SharedContext& context;
	Animator animpg;
	std::vector<AnimSet> animations;
public:
	

	int GetForza() const;
	void SetForza(int const& forza);
	void SetSprite(sf::Sprite newSprite);
	sf::Sprite& GetSprite();
	Animator* GetAnimpg() ;
	std::vector<AnimSet> GetAnimations() const;
	void Reset(const std::string& anim);
	void WeaponPosition(const char& direction);
	
	Arma(std::string nome, std::string pathIcona, std::string pathIconaAttivata, int forza, SharedContext& context) : Equipaggiamento(nome,pathIcona,pathIconaAttivata), forza(forza) , animpg(sprite),context(context) {}
	~Arma();
};