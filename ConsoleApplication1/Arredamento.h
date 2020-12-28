#pragma once
#include <SFML\Graphics\Sprite.hpp>
#include "Animator.h"
#include "SharedContext.h"
#include "Tile.h"
using AnimSet = Animator::Animation;
class Arredamento {
private:
	sf::Sprite sprite;
	std::vector<AnimSet> animations;
	std::string map;
	std::string nome;
	Animator animpg;
	sf::Vector2f position;
	Tile tile;
public:

	void SetSprite(const sf::Sprite &newSprite);
	sf::Sprite& GetSprite();
	Animator* GetAnimpg();
	std::vector<AnimSet> GetAnimations();
	void Position(const sf::Vector2f &pos);
	std::string GetMap();
	void SetMap(const std::string& newMap);
	std::string GetName();
	void PrepareTeleport(Tile* tile);
	void Teleport(SharedContext* context);

	Arredamento(const std::string& nome, const std::string& map, sf::Vector2f pos) ;
	~Arredamento();
};