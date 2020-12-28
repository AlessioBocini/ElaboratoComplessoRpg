#pragma once
#include "Skill.h"
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Text.hpp>
#include "SharedContext.h"
class Quickslot {
private:
	//Skill* skill;
	sf::Sprite Icon;
	sf::Text number;
	SharedContext& context;
	unsigned int id;
public:
	void Draw();
	void ConfigureQuickslot();
	Quickslot(SharedContext& context, unsigned int id);
	~Quickslot();
};