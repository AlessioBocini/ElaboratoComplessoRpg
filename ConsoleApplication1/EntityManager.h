#pragma once
#include <vector>
#include "Entita.h"
#include "SharedContext.h"
#include "NemicoComune.h"
#include "Miniboss.h"
#include "Giocatore.h"

using EntityContainer = std::unordered_map<unsigned int, Entita*>;
using EnemyTypes = std::unordered_map < std::string, std::string>;
using EntityFactory = std::unordered_map<EntityType, std::function<Entita* (void)>>;

class EntityManager {
public:

	EntityManager(SharedContext* context);
	~EntityManager();

	int Add(const EntityType& type, const std::string& name);
	void SetSpawnPoint(unsigned int id, sf::Vector2i);
	Entita* Find(unsigned int id);
	Entita* Find(const std::string& name);
	bool Remove(unsigned int id);
	
	void Setup();
	void Update(const sf::Time& elapsed);
	void Draw();
	std::vector<Nemico*> getEntities();
	Giocatore* GetGiocatore();
	void EraseAll();
	SharedContext* GetContext();
	

private:
	std::vector<Nemico*> entities;
	Giocatore* player;
	SharedContext* context;
};