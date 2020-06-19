#include "Mondo.h"
#include "GameManager.h"
#include <iostream>
Mondo::Mondo(SharedContext* context):context(context),tileCount(0),tileSetCount(0),maxMapSize(400,200)/*, loadNextMap(false)*/{
	context->gameMap = this;
	LoadTiles("D:/visualstudioprojects/ConsoleApplication1/assets/files/tiles.txt");
}
Mondo::~Mondo() {
	EraseTileSet();
	EraseMap();
	context->gameMap = nullptr;
}


Tile* Mondo::GetTileByCoords( int x,  int y) {

	auto id = GetTileIdByCoords(x, y);
	auto itr = tileMap.find(id);
	return (itr != tileMap.end()) ? itr->second : nullptr;
}


TileId Mondo::GetTileIdByCoords( int x,  int y) {
	return (x*maxMapSize.x) + y;
}

void Mondo::EraseMap() {
	/*for (auto it = tileMap.begin(); it != tileMap.end(); it++)
		delete it->second;*/
	tileCount = 0;
	tileMap.clear();
	//TODO potrei aver bisogno di un manager di entità?
	// per fare EraseAllEntities ?
}

void Mondo::EraseTileSet() {
	/*for (auto it = tileSet.begin(); it != tileSet.end(); it++)
		delete it->second;*/
	tileSet.clear();
	tileSetCount = 0;
}


const sf::Vector2f& Mondo::GetPlayerStartpoint() const {

	return playerStartPoint;
}
const sf::Vector2u& Mondo::GetMapSize() const {
	return maxMapSize;
}
unsigned int Mondo::GetTileSize() const {
	return Sheet::Tile_Size;
}
void Mondo::LoadTiles(const std::string& filepath) {
	std::ifstream file;
	file.open(filepath);
	if (!file.is_open()) { std::cout << "! Failed loading tile set file: " << filepath << std::endl; return; }
	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '|') { continue; }
		std::stringstream keystream(line);
		TileId tileId;
		std::string texture;
		keystream >> tileId>>texture;
		if (tileId < 0) { continue; }
		TileInfo* tile = new TileInfo(context,texture , tileId);
		keystream >> tile->name >> tile->friction.x >> tile->friction.y >> tile->deadly >> tile->blocked;
		if (tileId == 1) {
			auto& animation = tile->anim.CreateAnimation("animationTerra", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationTerra");
		}
		if (tileId == 3) {
				tile->sprite.setTextureRect(sf::IntRect(0, 0,Sheet::Tile_Size*2, Sheet::Tile_Size*2 ));
				auto& animation = tile->anim.CreateAnimation("animationAcquaGrande", texture, sf::seconds(1), true);
				animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size), sf::Vector2i(Sheet::Tile_Size*2, Sheet::Tile_Size*2), 3);
				tile->animation.push_back(animation);
				tile->anim.SwitchAnimation("animationAcquaGrande");	
		}
		if(tileId == 2 ) {
			auto& animation = tile->anim.CreateAnimation("animationStradapiccola", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(Sheet::Tile_Size*3, 0), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationStradapiccola");
			
		}
		if (tileId == 4) {
			auto& animation = tile->anim.CreateAnimation("animationMuro", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size*2), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationMuro");
		}
		if (tileId == 5) {
			auto& animation = tile->anim.CreateAnimation("animationCespuglio", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationCespuglio");
		}
		if (!tileSet.emplace(tileId, tile).second) {
			// Duplicate tile detected!
			std::cout << "! Duplicate tile type: " << tile->name << std::endl;
			delete tile;
		}
	}
	file.close();
}
void Mondo::LoadMap(const std::string& filepath) {
	/*
	T = terra

	S0 = strada Grande TODO
	00
	
	s = strada piccola

	A0 = Acqua grande
	00

	a = acqua piccola TODO
	P = Player
	N = Nemico TODO
	n = npc TODO
	# = muro

	c = cespuglio

	F0 = foresta grande TODO
	00

	f0 = albero TODO
	00

	*/
	std::ifstream file;
	file.open(filepath);
	if (!file.is_open()) { std::cout << "! Failed loading map file: " << filepath << std::endl; return; }
	std::string map;
	std::string line;
	bool isEntity = false;
	int k = 0;
	while (std::getline(file, map)) {
		std::stringstream keystream(map);
		
		char letter = 'l';
		
		keystream >> line;
		std::cout << line << std::endl;
		for (int i = 0; i < line.length(); i++) {
			isEntity = false;
			letter = line[i];
			TileId tileid;
			
			switch (letter)
			{
				case '#': {
					tileid = 4;
					break;
				}
				case 'N': {
					//coming soon.
					break;
				}
				case 'P': {
					tileid = 1;
					playerStartPoint = sf::Vector2f(i, k);
					break;
				}
				case 'T': {
					tileid = 1;
					break;
				}
				case 's': {
					tileid = 2;
					break;
				}
				case 'A': {
					tileid = 3;
					break;
				}
				case '1': { //default block
					tileid = 6;
					break; 
				}
				case '2': { //default deadly
					tileid = 7;
					break;
				} 
				case '3': { //default both deadly and blocked
					tileid = 8;
					break;
				}
				case 'c': {
					tileid = 5;
					break;
				}
				default: {
					std::cout << "error occurred" << std::endl;
					break;
				}
			}
			auto itr = tileSet.find(tileid);
			if (itr == tileSet.end())
					continue;
			sf::Vector2i tileCoords = sf::Vector2i(i, k );
			
			if (tileCoords.x > maxMapSize.x || tileCoords.y > maxMapSize.y) {
				std::cout << "! Tile is out of range: " << tileCoords.x << " " << tileCoords.y << std::endl;
				continue;
			}

			Tile* tile = new Tile();
			tile->properties = itr->second;

			if (!tileMap.emplace(GetTileIdByCoords(tileCoords.x, tileCoords.y), tile).second)
			{
				// Duplicate tile detected!
				std::cout << "! Duplicate tile! : " << tileCoords.x << " " << tileCoords.y << std::endl;
				delete tile;
				tile = nullptr;
				continue;
			}
		}
		k++;
	}
	file.close();


}
void Mondo::Update(sf::Time const& dt) {
	for (auto it : tileMap) {
			it.second->properties->anim.update(dt);
	}

	sf::FloatRect viewSpace = context->wind->GetViewSpace();
	//background.setPosition(viewspace.left, viewspace.top);
}
void Mondo::Draw() {
	sf::RenderWindow* wind = context->wind->GetRenderWindow();
	sf::FloatRect viewSpace = context->wind->GetViewSpace();
	//wind->draw(background);
	sf::Vector2i tileBegin(floor(viewSpace.left / Sheet::Tile_Size), floor(viewSpace.top / Sheet::Tile_Size));
	sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size),ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size));
	unsigned int count = 0;
	for (int x = tileBegin.x; x <= tileEnd.x; ++x) {
		for (int y = tileBegin.y; y <= tileEnd.y; ++y) {
			if (x < 0 || y < 0) { continue; }
			Tile* tile = GetTileByCoords(x, y);
			if (!tile) { continue; }
			sf::Sprite& sprite = tile->properties->sprite;
			sprite.setPosition(x * Sheet::Tile_Size, y * Sheet::Tile_Size);
			wind->draw(sprite);
			++count;

		}
	}
}
