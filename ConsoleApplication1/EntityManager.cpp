#include "EntityManager.h"


#include "GameManager.h"
#include "Mondo.h"

EntityManager::EntityManager(SharedContext* context) :player(new Giocatore("alessio",sf::Vector2f(0,0))){
	this->context = context;
}
void EntityManager::Setup() {
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
int EntityManager::Add(const EntityType& type, const std::string& name) {
	std::string name1 = name;
	sf::Vector2f pos = sf::Vector2f(5.0f, 2.0f);
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
	player->ResolveCollisions(context);

	for (auto i : entities) {
		i->animpg.update(dt);
		if(!i->isblockedD)
			i->Movimento(i->GetVelocita(),0);
		//check collissions mobs
		i->CheckCollisions(context);
		i->ResolveCollisions(context);
	}
	
	
}


