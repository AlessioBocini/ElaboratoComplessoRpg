#pragma once
#include <vector>
#include <SFML\System\Vector2.hpp>
#include "Tile.h"
#include "Giocatore.h"
#include "BaseState.h"
#include "Arredamento.h"
#include "DecorationManager.h"
using TileMap = std::unordered_map<TileId, Tile*>;
using TileSet = std::unordered_map<TileId, TileInfo*>;

class GameManager;

class Territorio {
private:
	TileId GetTileIdByCoords(int x, int y);
	
	
	BaseState* currentState;
	bool loadNextMap;
	std::string nextMap;
	//float mapGravity; se aggiungessi la possibilità di saltare.
	int propretario;
	sf::Vector2u maxMapSize;
	sf::Vector2f playerStartPoint;
	TileMap tileMap;
	unsigned int tileCount;
	SharedContext* context;
	std::string currentTerritory;
	DecorationManager* deco;
public:
	Territorio(SharedContext* context);
	~Territorio();
	

	void EraseMap();
	Tile* GetTileByCoords(int x, int y);
	//TileInfo* GetDefaultTile();
	std::string GetCurrentTerritory() const;
	void SetCurrentTerritory(const std::string& territory);
	Arredamento* GetDecorationByCoords(int x, int y);
	DecorationManager* GetDecorationManager();
	const sf::Vector2u& GetMapSize() const;
	const sf::Vector2f& GetPlayerStartpoint() const;
	void SetPlayerStartpoint(const sf::Vector2f& newpos);
	void LoadMap(const std::string& path, bool first);
	void Update(sf::Time const& dt);
	void Draw();

	

};