#pragma once
#include <vector>
#include "Entita.h"
#include "SharedContext.h"
#include "Miniboss.h"
#include "Giocatore.h"
#include "NPC.h"

using EntityContainer = std::unordered_map<unsigned int, Entita*>;
using EnemyTypes = std::unordered_map < std::string, std::string>;
using EntityFactory = std::unordered_map<EntityType, std::function<Entita* (void)>>;

class EntityManager {
public:

	EntityManager(SharedContext& context);
	~EntityManager();

	int Add(const EntityType& type, const std::string& name, const std::string & filepath, const int& details);
	void SetSpawnPoint(unsigned int id, sf::Vector2i);
	Entita* Find(unsigned int id);
	bool Remove(unsigned int id);

	void ConfigurePlayer();
	void Update(const sf::Time& elapsed);
	void Draw();
	std::vector<Entita*> getEntities();
	Giocatore* GetGiocatore();
	void EraseAll();


private:
	std::vector<Entita*> entities;
	Giocatore player;
	SharedContext& context;
};