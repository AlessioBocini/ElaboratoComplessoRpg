#pragma once
#include <vector>
#include <SFML\System\Vector2.hpp>
#include "Territorio.h"
#include "GameManager.h"
class Mondo {
private:
	GameManager manager;
	sf::Vector2i size;
	int nTerritori;
	std::vector<Territorio> territori;
public:
	sf::Vector2i GetSize() {
		return this->size;
	}
	int GetNTerritori() {
		return this->nTerritori;
	}
};