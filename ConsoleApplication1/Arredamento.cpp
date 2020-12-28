#include "Arredamento.h"
#include "GameManager.h"

void Arredamento::SetSprite(const sf::Sprite &newSprite)
{
	this->sprite = newSprite;
}

sf::Sprite& Arredamento::GetSprite()
{
	return this->sprite;
}

Animator* Arredamento::GetAnimpg()
{
	return &animpg;
}

std::vector<AnimSet> Arredamento::GetAnimations()
{
	return animations;
}

void Arredamento::Position(const sf::Vector2f &pos)
{
	sf::Vector2i spritesize = sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size);
	sprite.setPosition(pos.x * spritesize.x, pos.y * spritesize.y);
}

std::string Arredamento::GetMap()
{
	return map;
}

void Arredamento::SetMap(const std::string& newMap)
{
	map = newMap;
}

std::string Arredamento::GetName()
{
	return nome;
}

void Arredamento::PrepareTeleport(Tile* tile)
{
	this->tile = *tile;
}

void Arredamento::Teleport(SharedContext* context)
{
	Mondo* world = context->gameMap;
	context->gameManager->SetPlayerStart(tile.teleportPos);
	world->SetPrevMap(tile.nextMap);//setto quale è la mappa precedente.
	world->ChangeActualMap(tile.nextMap);
	world->getActualMap().SetPlayerStartpoint(tile.teleportPos);//definisco il nuovo spawnpoint
}

Arredamento::Arredamento(const std::string& nome, const std::string& map, sf::Vector2f pos) : animpg(sprite), nome(nome), position(pos), map(map)
{
	Position(position);
}

Arredamento::~Arredamento(){}
