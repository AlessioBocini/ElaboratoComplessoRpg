#include "EntityManager.h"


#include "GameManager.h"
#include "Mondo.h"

EntityManager::EntityManager(SharedContext* context) :player(new Giocatore("alessio", sf::Vector2f(0, 0))) , context(context){
	
}
void EntityManager::ConfigurePlayer() {
	
	player->GetSprite().setTextureRect(sf::IntRect(0, 0, context->gameManager->spriteSize.x, context->gameManager->spriteSize.y));
	auto& animationA = player->animpg.CreateAnimation("animationA", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationA.AddFrames(sf::Vector2i(0, context->gameManager->spriteSize.y), context->gameManager->spriteSize, 3);
	auto& animationidle = player->animpg.CreateAnimation("animationS", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationidle.AddFrames(sf::Vector2i(0, 0), context->gameManager->spriteSize, 3);
	auto& animationD = player->animpg.CreateAnimation("animationD", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationD.AddFrames(sf::Vector2i(0, context->gameManager->spriteSize.y * 2), context->gameManager->spriteSize, 3);
	auto& animationW = player->animpg.CreateAnimation("animationW", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationW.AddFrames(sf::Vector2i(0, context->gameManager->spriteSize.y * 3), context->gameManager->spriteSize, 3);
}
EntityManager::~EntityManager() {
	delete player;
	for (auto i : entities)
		delete i;

	entities.clear();
}
Giocatore* EntityManager::GetGiocatore() {
	return player;
}
std::vector<Nemico*> EntityManager::getEntities() {
	return entities;
}
std::vector<Npc*> EntityManager::getNpcs()
{
	return vectorNpc;
}
int EntityManager::Add(const EntityType& type, const std::string& name) {
	std::string name1 = name;
	sf::Vector2f pos = sf::Vector2f(5.0f, 2.0f);
	std::string map = context->gameMap->GetPrevMap();
	if (type == EntityType::Guard) {

	}
	if (type == EntityType::Shopkeeper) {
		Npc* n = new Npc(name1, 0, 100, 1, 0.6f, pos, 3, context, "Shopkeeper");
		auto& animationeShopkeeperA = n->animpg.CreateAnimation("animationeShopkeeperA", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
		animationeShopkeeperA.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 3, context->gameManager->spriteSize.y), context->gameManager->spriteSize, 3);
		n->animations.push_back(animationeShopkeeperA);

		auto& animationeShopkeeperS = n->animpg.CreateAnimation("animationeShopkeeperS", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
		animationeShopkeeperS.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 3, 0), context->gameManager->spriteSize, 3);
		n->animations.push_back(animationeShopkeeperS);

		auto& animationeShopkeeperD = n->animpg.CreateAnimation("animationeShopkeeperD", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
		animationeShopkeeperD.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 3, context->gameManager->spriteSize.y * 2), context->gameManager->spriteSize, 3);
		n->animations.push_back(animationeShopkeeperD);

		auto& animationeShopkeeperW = n->animpg.CreateAnimation("animationeShopkeeperW", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
		animationeShopkeeperW.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 3, context->gameManager->spriteSize.y * 3), context->gameManager->spriteSize, 3);
		n->animations.push_back(animationeShopkeeperW);

		auto& animationeShopkeeperIDLEW = n->animpg.CreateAnimation("animationeShopkeeperIDLEW", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
		animationeShopkeeperIDLEW.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 4, context->gameManager->spriteSize.y * 3), context->gameManager->spriteSize, 1);
		n->animations.push_back(animationeShopkeeperIDLEW);

		auto& animationeShopkeeperIDLED = n->animpg.CreateAnimation("animationeShopkeeperIDLED", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
		animationeShopkeeperIDLED.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 4, context->gameManager->spriteSize.y * 2), context->gameManager->spriteSize, 1);
		n->animations.push_back(animationeShopkeeperIDLED);

		auto& animationeShopkeeperIDLEA = n->animpg.CreateAnimation("animationeShopkeeperIDLEA", "../assets/images/pack/Characters/people1.png", sf::seconds(1), true);
		animationeShopkeeperIDLEA.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 4, context->gameManager->spriteSize.y), context->gameManager->spriteSize, 1);
		n->animations.push_back(animationeShopkeeperIDLEA);

		n->animpg.SwitchAnimation("animationeShopkeeperIDLEW");
		n->setMap(map);
		vectorNpc.push_back(n);
	}


	//TODO Miniboss
	if (type == EntityType::Enemy) {
		NemicoComune* n = new NemicoComune(name1, 0, 100, 1, 0.6f, pos, 2, context, "Nemico1");
		auto& animationenemyA = n->animpg.CreateAnimation("animationenemyA", "../assets/images/pack/Characters/people2.png", sf::seconds(1), true);
		animationenemyA.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 9, context->gameManager->spriteSize.y), context->gameManager->spriteSize, 3);
		n->animations.push_back(animationenemyA);

		auto& animationenemyS = n->animpg.CreateAnimation("animationenemyS", "../assets/images/pack/Characters/people2.png", sf::seconds(1), true);
		animationenemyS.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 9, 0), context->gameManager->spriteSize, 3);
		n->animations.push_back(animationenemyS);

		auto& animationenemyD = n->animpg.CreateAnimation("animationenemyD", "../assets/images/pack/Characters/people2.png", sf::seconds(1), true);
		animationenemyD.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 9, context->gameManager->spriteSize.y * 2), context->gameManager->spriteSize, 3);
		n->animations.push_back(animationenemyD);

		auto& animationenemyW = n->animpg.CreateAnimation("animationenemyW", "../assets/images/pack/Characters/people2.png", sf::seconds(1), true);
		animationenemyW.AddFrames(sf::Vector2i(context->gameManager->spriteSize.x * 9, context->gameManager->spriteSize.y * 3), context->gameManager->spriteSize, 3);
		n->animations.push_back(animationenemyW);

		n->animpg.SwitchAnimation("animationenemyD");
		entities.push_back(n);
	}
	return 0;

}


void EntityManager::Update(const sf::Time& dt) {
	player->CheckCollisions(context);

	for (auto i : entities) {
		i->animpg.update(dt);
		if (!i->isblockedD)
			i->Movimento((i->GetVelocita()), 0);

		i->CheckCollisions(context);
		i->CollisionEntity(player, context);
		player->CollisionEntity(i, context);
		for (auto k : entities) {
			if (i == k)
				continue;
			i->CollisionEntity(k, context);
		}		
	}
	for (auto i : vectorNpc) {
		i->animpg.update(dt);
	}
	for (auto i : entities) {
		i->ResolveCollisions(context);
	}
	player->ResolveCollisions(context);

	
}

void EntityManager::Draw() {


	
}
