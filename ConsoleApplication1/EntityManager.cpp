#include "EntityManager.h"

#include "GameManager.h"
#include "Mondo.h"

EntityManager::EntityManager(SharedContext& context) :player("alessio", sf::Vector2f(0, 0),context) , context(context),id(1){}
void EntityManager::ConfigurePlayer() {
	Animator* animpg = player.GetAnimpg();
	player.setSpawnPoint(context.gameMap->getActualMap().GetPlayerStartpoint());
	sf::Vector2i spritesize = context.gameManager->GetSpriteSize();
	auto& animationA = animpg->CreateAnimation("animationA", "assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationA.AddFrames(sf::Vector2i(0, spritesize.y), spritesize, 3);
	auto& animationS = animpg->CreateAnimation("animationS", "assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationS.AddFrames(sf::Vector2i(0, 0), spritesize, 3);
	auto& animationD = animpg->CreateAnimation("animationD", "assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationD.AddFrames(sf::Vector2i(0, spritesize.y * 2), spritesize, 3);
	auto& animationW = animpg->CreateAnimation("animationW", "assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationW.AddFrames(sf::Vector2i(0, spritesize.y * 3), spritesize, 3);

	auto& animationIdleA = animpg->CreateAnimation("animationIDLEA", "assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationIdleA.AddFrames(sf::Vector2i(spritesize.x, spritesize.y), spritesize, 1);
	auto& animationIdleS = animpg->CreateAnimation("animationIDLES", "assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationIdleS.AddFrames(sf::Vector2i(spritesize.x, 0), spritesize, 1);
	auto& animationIdleD = animpg->CreateAnimation("animationIDLED", "assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationIdleD.AddFrames(sf::Vector2i(spritesize.x, spritesize.y * 2), spritesize, 1);
	auto& animationIdleW = animpg->CreateAnimation("animationIDLEW", "assets/images/pack/Characters/people1.png", sf::seconds(1), true);
	animationIdleW.AddFrames(sf::Vector2i(spritesize.x, spritesize.y * 3), spritesize, 1);
	auto& animationDeath = animpg->CreateAnimation("animationDeath", "assets/images/pack/Characters/deathanimations.png", sf::seconds(1), true);
	animationDeath.AddFrames(sf::Vector2i(0, 0), spritesize, 4);


	player.GetInventario()->ConfiguraEquip();
	for (int i = 0; i < 3; i++) {
		Quickslot test = Quickslot(context,i+1);
		player.GetQuickslots()->push_back(test);
		player.GetQuickslots()->at(i).ConfigureQuickslot();
	}
	
	
	
}
EntityManager::~EntityManager() {
	EraseAll();
}
Giocatore* EntityManager::GetGiocatore() {
	return &player;
}
std::vector<Entita*> EntityManager::getEntities() const {
	return entities;
}

int EntityManager::Add(const EntityType& type, const std::string& name, const std::string& filepath, const int& details) {
	std::string name1 = name;
	sf::Vector2f pos = sf::Vector2f(7.0f, 3.0f);
	sf::Vector2i spritesize = context.gameManager->GetSpriteSize();
	int posX = 0, posY = 0;
	std::string path = "";
	if (type == EntityType::NPC) {
		Npc* n = new Npc(name1, 0, 100, 1, 60, pos, id, context);
		Animator* animpg = n->GetAnimpg();
		if (details == int(NpcType::Shopkeeper)) {
			n->SetEntityType("Shopkeeper");
			posY = spritesize.y;
			posX = spritesize.x * 3;
			path = "assets/images/pack/Characters/people1.png";
		}
		auto& animationeShopkeeperA = animpg->CreateAnimation("animationA", path, sf::seconds(1), true);
		animationeShopkeeperA.AddFrames(sf::Vector2i(posX,posY), spritesize, 3);
		n->GetAnimations().push_back(animationeShopkeeperA);

		auto& animationeShopkeeperS = animpg->CreateAnimation("animationS", path, sf::seconds(1), true);
		animationeShopkeeperS.AddFrames(sf::Vector2i(posX, 0), spritesize, 3);
		n->GetAnimations().push_back(animationeShopkeeperS);

		auto& animationeShopkeeperD = animpg->CreateAnimation("animationD", path, sf::seconds(1), true);
		animationeShopkeeperD.AddFrames(sf::Vector2i(posX, posY * 2), spritesize, 3);
		n->GetAnimations().push_back(animationeShopkeeperD);

		auto& animationeShopkeeperW = animpg->CreateAnimation("animationW", path, sf::seconds(1), true);
		animationeShopkeeperW.AddFrames(sf::Vector2i(posX, posY * 3), spritesize, 3);
		n->GetAnimations().push_back(animationeShopkeeperW);

		auto& animationeShopkeeperIDLEW = animpg->CreateAnimation("animationIDLEW", path, sf::seconds(1), true);
		animationeShopkeeperIDLEW.AddFrames(sf::Vector2i(spritesize.x + posX, posY * 3), spritesize, 1);
		n->GetAnimations().push_back(animationeShopkeeperIDLEW);

		auto& animationeShopkeeperIDLED = animpg->CreateAnimation("animationIDLED", path, sf::seconds(1), true);
		animationeShopkeeperIDLED.AddFrames(sf::Vector2i(spritesize.x + posX, posY * 2), spritesize, 1);
		n->GetAnimations().push_back(animationeShopkeeperIDLED);

		auto& animationeShopkeeperIDLEA = animpg->CreateAnimation("animationIDLEA", path, sf::seconds(1), true);
		animationeShopkeeperIDLEA.AddFrames(sf::Vector2i(spritesize.x + posX, posY), spritesize, 1);
		n->GetAnimations().push_back(animationeShopkeeperIDLEA);

		animpg->SwitchAnimation("animationIDLEW");
		n->setMap(filepath);
		n->setTypeOfNpc(details);
		entities.push_back(n);
	}


	//TODO Miniboss
	if (type == EntityType::Enemy) {
		Nemico* n = new Nemico(name1, 3 , 100, 1, 60, pos, id, context);
		Animator* animpg = n->GetAnimpg();
		if (details == int(EnemyType::Skeleton)) {
			n->SetEntityType("Nemico1");
			posY = spritesize.y;
			posX = spritesize.x * 9;
			path = "assets/images/pack/Characters/people2.png";
		}
		auto& animationenemyA = animpg->CreateAnimation("animationA", path, sf::seconds(1), true);
		animationenemyA.AddFrames(sf::Vector2i(posX, posY), spritesize, 3);
		n->GetAnimations().push_back(animationenemyA);

		auto& animationenemyS = animpg->CreateAnimation("animationS", path, sf::seconds(1), true);
		animationenemyS.AddFrames(sf::Vector2i(posX, 0), spritesize, 3);
		n->GetAnimations().push_back(animationenemyS);

		auto& animationenemyD = animpg->CreateAnimation("animationD", path, sf::seconds(1), true);
		animationenemyD.AddFrames(sf::Vector2i(posX, posY * 2), spritesize, 3);
		n->GetAnimations().push_back(animationenemyD);

		auto& animationenemyW = animpg->CreateAnimation("animationW", path, sf::seconds(1), true);
		animationenemyW.AddFrames(sf::Vector2i(posX, posY * 3), spritesize, 3);
		n->GetAnimations().push_back(animationenemyW);

		//cambia
		auto& animationenemyDeath = animpg->CreateAnimation("animationDeath","assets/images/pack/Tilesets/AH_B.png" , sf::seconds(1), true);
		animationenemyDeath.AddFrames(sf::Vector2i(Tile_Size*5, Tile_Size * 7), spritesize, 1);
		n->GetAnimations().push_back(animationenemyW);

		animpg->SwitchAnimation("animationD");
		n->setMap(filepath);
		n->SetEnemyType(details);
		entities.push_back(n);
	}
	id++;
	return 0;

}

Entita* EntityManager::Find(unsigned int id)
{
	Entita* ent = nullptr;

	for (auto it : entities) {
		if (it->GetId() == id) {
			ent = it;
			break;
		}
	}

	return ent;
}

bool EntityManager::Remove(unsigned int id)
{
	bool result = false;
	//std::vector<Entita*>::iterator i;
	for (auto it = entities.begin(); it != entities.end(); it++) {
		if (id == (*it)->GetId()) {
			//i = it;
			result = true;
			entities.erase(it);
			break;
		}
	}
	
	return result;
}

void EntityManager::Update(const sf::Time& dt) {
	player.CheckCollisions();
	player.GetInventario()->UpdateItems(dt);

	std::string currentTerritory = context.gameMap->getActualMap().GetCurrentTerritory();

	for (Entita* i : entities) {
		if (i->getMap() != currentTerritory)
			continue;
	
		Nemico* Enemy = dynamic_cast<Nemico*>(i);
		if(Enemy != nullptr)
			Enemy->PreparaMovimento(); //movimento per i nemici

		if (!i->isAlive())
		{
			if (i->getDespawnClock().getElapsedTime().asSeconds() > i->getDespawnTime()) {
				i->setVisible(false);
				i->Respawn();
				continue;
			}
			
		}
			
		i->Update(dt);
		i->CheckCollisions();
		i->CollisionEntity(&player);
		player.CollisionEntity(i);
		for (Entita* k : entities) {
			if (i == k)
				continue;
			i->CollisionEntity(k);
		}		
	}

	for (Entita* i : entities) {
		i->ResolveCollisions();
	}
	player.ResolveCollisions();
}

void EntityManager::Draw() {
	float nametextweight = 0.5, infoweight = 0.25;
	Window* m_window = context.wind;
	AssetManager* assetmanager = context.assetManager;
	sf::FloatRect globalBoundsPlayer = player.GetSprite().getGlobalBounds();
	sf::Vector2f positionPlayer = player.GetPosition();
	//disegno caratteristiche giocatore
	sf::Text name(player.GetNome(), assetmanager->GetFont("arial.ttf"));
	sf::Text level("[" + std::to_string(player.GetLivello()) + "]", assetmanager->GetFont("arial.ttf"));
	sf::Text vitalita("HP: " + std::to_string(player.GetVitalita()), assetmanager->GetFont("arial.ttf"));
	sf::Text stamina("SP: " + std::to_string(player.GetStamina()), assetmanager->GetFont("arial.ttf"));
	sf::Text coords("x : " + std::to_string(positionPlayer.x / 32) + "\ny : " + std::to_string(positionPlayer.y / 32), assetmanager->GetFont("arial.ttf"));

	name.setScale(nametextweight, nametextweight);
	name.setOutlineColor(sf::Color::Black);
	name.setOutlineThickness(1);
	level.setScale(nametextweight, nametextweight);
	level.setOutlineColor(sf::Color::Black);
	level.setOutlineThickness(1);
	stamina.setScale(infoweight, infoweight);
	stamina.setOutlineColor(sf::Color::Black);
	stamina.setOutlineThickness(0.25);
	stamina.setFillColor(sf::Color::Blue);
	vitalita.setScale(infoweight, infoweight);
	vitalita.setOutlineColor(sf::Color::Black);
	vitalita.setOutlineThickness(0.25);
	vitalita.setFillColor(sf::Color::Red);
	coords.setScale(nametextweight, nametextweight);
	coords.setFillColor(sf::Color::Red);

	

	coords.setPosition(m_window->GetViewSpace().left, m_window->GetViewSpace().top);
	name.setPosition(positionPlayer.x - (globalBoundsPlayer.width) / 4 - 15, positionPlayer.y - globalBoundsPlayer.height);
	vitalita.setPosition(positionPlayer.x - (globalBoundsPlayer.width) / 4 - 15, positionPlayer.y - globalBoundsPlayer.height / 3);
	stamina.setPosition(positionPlayer.x + (globalBoundsPlayer.width) - 1 / 4 - 15, positionPlayer.y - globalBoundsPlayer.height / 3);
	level.setPosition(positionPlayer.x + (globalBoundsPlayer.width) + player.GetNome().size(), positionPlayer.y - globalBoundsPlayer.height);
	m_window->Draw(player.GetSprite());
	
	player.GetInventario()->DrawItems();

	//disegno le caratteristiche dei nemici
	sf::Text nameEne;
	sf::Text levelEne;
	sf::Text vitalitaEne;
	std::string currentTerritory = context.gameMap->getActualMap().GetCurrentTerritory();
	
	Mondo* world = context.gameMap;
	for (Entita* i : getEntities()) {

		if (i->getMap() != currentTerritory) continue;
		if (!i->isVisible()) continue;
		m_window->Draw(i->GetSprite());

		Miniboss* psMiniboss = dynamic_cast<Miniboss*>(i);
		if (!(psMiniboss == nullptr)) {
			std::cout << "i'm a boss" << std::endl;
		}

		sf::FloatRect globalBoundsEntity = i->GetSprite().getGlobalBounds();
		sf::Vector2f positionEntity = i->GetPosition();

		if (i->getMap() != currentTerritory)
			continue;


		Npc* psNpc = dynamic_cast<Npc*>(i);
		if (psNpc == nullptr) {
			nameEne = sf::Text(i->GetNome(), assetmanager->GetFont("arial.ttf"));
			levelEne = sf::Text("[" + std::to_string(i->GetLivello()) + "]", assetmanager->GetFont("arial.ttf"));
			vitalitaEne = sf::Text("HP: " + std::to_string(i->GetVitalita()), assetmanager->GetFont("arial.ttf"));
			nameEne.setScale(nametextweight, nametextweight);
			nameEne.setOutlineColor(sf::Color::Black);
			nameEne.setOutlineThickness(1);
			levelEne.setScale(nametextweight, nametextweight);
			levelEne.setOutlineColor(sf::Color::Black);
			levelEne.setOutlineThickness(1);
			vitalitaEne.setScale(infoweight, infoweight);
			vitalitaEne.setOutlineColor(sf::Color::Black);
			vitalitaEne.setOutlineThickness(0.25);
			vitalitaEne.setFillColor(sf::Color::Red);
			nameEne.setPosition(positionEntity.x - (globalBoundsEntity.width) / 4 - 15, positionEntity.y - globalBoundsEntity.height);
			vitalitaEne.setPosition(positionEntity.x - (globalBoundsEntity.width) / 3, positionEntity.y - globalBoundsEntity.height / 3);
			levelEne.setPosition(positionEntity.x + (globalBoundsEntity.width) + i->GetNome().size(), positionEntity.y - globalBoundsEntity.height);
			if (i->isAlive()) {
				m_window->Draw(nameEne);
				m_window->Draw(levelEne);
				m_window->Draw(vitalitaEne);
			}
			
		}
	}

	
	m_window->Draw(name);
	m_window->Draw(level);
	m_window->Draw(vitalita);
	m_window->Draw(stamina);
	m_window->Draw(coords);

	player.GetInventario()->DrawInventory(); 
	//disegno inventario
	for (int i = 0; i < player.GetQuickslots()->size(); i++) {
		player.GetQuickslots()->at(i).Draw(); 
		// disegno le sprite dei quickslot
	}
}
void EntityManager::EraseAll() {
	for (Entita* i : entities)
		delete i;

	entities.clear();
}
