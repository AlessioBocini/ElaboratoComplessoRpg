#pragma once
#include <vector>
#include <SFML\System\Vector2.hpp>
#include "Territorio.h"
#include "Tile.h"
#include "BaseState.h"
#include "Giocatore.h"
using TileMap = std::unordered_map<TileId, Tile*>;
using TileSet = std::unordered_map<TileId, TileInfo*>;

class GameManager;

class Mondo {
private:
	TileId GetTileIdByCoords( int x,  int y);
	void LoadTiles(const std::string& path);
	void EraseMap();
	void EraseTileSet();
	SharedContext* context;
	BaseState* currentState;
	/*bool loadNextMap;
	std::string nextMap;*/
	//float mapGravity; se aggiungessi la possibilità di saltare.
	unsigned int tileSetCount;
	unsigned int tileCount;
	sf::Vector2u maxMapSize;
	sf::Vector2f playerStartPoint;
	TileSet tileSet;
	TileMap tileMap;
	int nTerritori;
	std::vector<Territorio> territori;
public:
	Mondo(SharedContext* context);
	~Mondo();
	Tile* GetTileByCoords( int x,  int y);
	TileInfo* GetDefaultTile();
	unsigned int GetTileSize() const;
	const sf::Vector2u& GetMapSize() const;
	const sf::Vector2f& GetPlayerStartpoint() const;
	void LoadMap(const std::string& path);
	//void LoadNext();
	void Update(sf::Time const& dt);
	void Draw();
	int GetNTerritori() {
		return this->nTerritori;
	}
};