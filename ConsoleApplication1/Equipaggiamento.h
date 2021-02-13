#pragma once
#include <string>
#include <SFML\Graphics\Sprite.hpp>
#include "Animator.h"
#include "SharedContext.h"

using AnimSet = Animator::Animation;
class Equipaggiamento {
protected:
	std::vector<AnimSet> animationsIcon;
	Animator animpgIcon;
	std::string nome;
	sf::Sprite icona;
	std::string pathicona;
	std::string pathiconaAttivata;
	bool usingItem;
public:
	std::string GetNomeEquip() const {
		return this->nome;
	}
	void SetNomeEquip(std::string nome) {
		this->nome = nome;
	}
	std::string GetIcon() const {
		return this->pathicona;
	}
	void SetIcon(std::string path) {

		this->pathicona = nome;
	}
	std::string GetIconActivated() const {
		return this->pathiconaAttivata;
	}
	void SetIconActicated(std::string nome) {
		this->pathiconaAttivata = nome;
	}

	bool GetUsing() const{
		
		return usingItem;
	}
	void SetUsing(bool value) {
		usingItem = value;
	}
	sf::Sprite getIconSprite() {
		return this->icona;
	}
	
	void ToggleIcon() {
		if (animpgIcon.GetCurrentAnimationName() == "normale") {
			animpgIcon.SwitchAnimation("attivata");
			usingItem = true;
		}
		else {
			animpgIcon.SwitchAnimation("normale");
			usingItem = false;
		}
	}
	Equipaggiamento(std::string nome,std::string icona,std::string iconaAttiva) : nome(nome),pathicona(icona), pathiconaAttivata(iconaAttiva), animpgIcon(this->icona),usingItem(false) {
		auto& anim1 = animpgIcon.CreateAnimation("normale", pathicona, sf::seconds(1), false);
		anim1.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(32, 32), 1);
		auto& anim2 = animpgIcon.CreateAnimation("attivata", pathiconaAttivata, sf::seconds(1), false);
		anim2.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(32, 32), 1);
		animationsIcon.push_back(anim1);
		animationsIcon.push_back(anim2);
		animpgIcon.SwitchAnimation("normale");
	}
};