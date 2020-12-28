#pragma once
#pragma once
#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Nemico {
public:
	Nemico(sf::Vector2f pos):pos(pos){}

	~Nemico() {}
	void PreparaMovimento();
	int GetEnemyType() {
		return enemyType;
	}
	void SetEnemyType(const int& type) {
		enemyType = type;
	}
	sf::FloatRect GetCollRect() {
		return rectColl;
	}
	void updateCollRect() {
		rectColl = sf::FloatRect(pos.x, pos.y, 20, 26);
	}
	sf::Vector2f *GetPos() {
		return &pos;
	}
private:
	int enemyType;
	sf::Vector2f pos;
	sf::FloatRect rectColl;
};

using TileId = unsigned int;
struct TileInfo {
	TileInfo(const std::string& texture = "", TileId id = 0) : id(0), texture(texture), blocked(false), deadly(false) {
		if (texture == "") {
			this->id = id;
			return;
		}

		this->id = id;
		sf::IntRect tileBoundaries(this->id % (1366 / 32) * 32, this->id / (720 / 32) * 32,
			32, 32);
		sf::Texture texture1;
		texture1.loadFromFile("../assets/images/cel2.png");
		sprite.setTexture(texture1);
		sprite.setTextureRect(tileBoundaries);

	}
	~TileInfo() {

	}
	sf::Sprite sprite;
	TileId id;
	std::string name;
	sf::Vector2f friction;
	bool deadly;
	bool blocked;
	std::string texture;

};

struct Tile {

	TileInfo properties;
	bool teleport;
	std::string nextMap;
	Tile() : teleport(false), nextMap("") {}
	~Tile() {

	}
};

using TileSet = std::unordered_map<TileId, TileInfo>;
using TileMap = std::unordered_map<TileId, Tile>;
sf::FloatRect rectColl;
sf::Vector2f position;
TileSet tileSet;
TileMap tileMap;
sf::Vector2f playerStartPoint;
sf::Vector2f enemyStartPoint;



void updateCollRect() {
	rectColl = sf::FloatRect(position.x, position.y, 20, 26);
}

bool Movimento(int x, int y) {

	position += sf::Vector2f(x*32, y*32);
	updateCollRect();

	return true;
}





sf::Vector2u maxMapSize = sf::Vector2u(400, 200);




TileId GetTileIdByCoords(int x, int y) {
	return (x * maxMapSize.x) + y;
}

Tile GetTileByCoords(int x, int y) {
	TileId id = GetTileIdByCoords(x, y);
	auto itr = tileMap.begin();
	if (itr != tileMap.end())
		return itr->second;

	Tile tile;
	return tile;
}

int  CheckCollisions(const std::string& world) {
	unsigned int tileSize = 32;


	int fromX = floor(rectColl.left / tileSize);
	int toX = floor((rectColl.left + rectColl.width) / tileSize);
	int fromY = floor(rectColl.top / tileSize);
	int toY = floor((rectColl.top + rectColl.height) / tileSize);


	for (int x = fromX; x <= toX; ++x) {
		for (int y = fromY; y <= toY; ++y) {
			Tile tile = GetTileByCoords(x, y);
			if (!tile.properties.blocked && !tile.teleport)continue;
			sf::FloatRect tileBounds = sf::FloatRect(x * tileSize, y * tileSize, tileSize, tileSize);
			sf::FloatRect intersection;
			rectColl.intersects(tileBounds, intersection);
			if (tile.teleport) {
				return 2;
			}
			return 1;
		}
	}
	return 0;
}
bool  CheckCollisionsDeadly(const std::string& world) {
	unsigned int tileSize = 32;


	int fromX = floor(rectColl.left / tileSize);
	int toX = floor((rectColl.left + rectColl.width) / tileSize);
	int fromY = floor(rectColl.top / tileSize);
	int toY = floor((rectColl.top + rectColl.height) / tileSize);


	for (int x = fromX; x <= toX; ++x) {
		for (int y = fromY; y <= toY; ++y) {
			Tile tile = GetTileByCoords(x, y);
			//if (!tile.properties.blocked && !tile.teleport)continue;
			if (!tile.properties.deadly) continue;
			sf::FloatRect tileBounds = sf::FloatRect(x * tileSize, y * tileSize, tileSize, tileSize);
			sf::FloatRect intersection;
			rectColl.intersects(tileBounds, intersection);
			return true;
		}
	}
	return false;
}



void LoadTiles(const std::string& filepath) {
	std::ifstream file;
	file.open(filepath);
	if (!file.is_open()) { std::cout << "! Failed loading tile set file: " << filepath << std::endl; return; }
	std::string line;
	while (std::getline(file, line)) {
		if (line[0] == '|') { continue; }
		std::stringstream keystream(line);
		TileId tileId;
		std::string texture;
		keystream >> tileId >> texture;
		if (tileId < 0) { continue; }
		TileInfo tile(texture, tileId);

		keystream >> tile.name >> tile.friction.x >> tile.friction.y >> tile.deadly >> tile.blocked;
		if (!tileSet.emplace(tileId, tile).second) {
			// Duplicate tile detected!
		}
	}
	file.close();

}

void LoadMap(const std::string& filepath, bool first, Nemico* ent =nullptr) {
	std::string path = "../assets/files/mock/";
	std::string postfix = ".map";
	std::ifstream file;
	file.open(path + filepath + postfix);
	if (!file.is_open()) { std::cout << "! Failed loading map file: " << filepath << std::endl; return; }
	std::string map;
	std::string line;
	bool isEntity = false;
	int k = 0;
	while (std::getline(file, map)) {
		std::stringstream keystream(map);

		char letter = 'l';
		keystream >> line;

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
			case 'E': {
				enemyStartPoint = sf::Vector2f(i, k);
				break;
			}
			case 'P': {

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
			case 'm': {
				if (filepath == "casa")
					tileid = 9;
				else
					tileid = 17;
				break;
			}
			case 'p': {
				tileid = 10;
				break;
			}
			case 'l': {

				tileid = 11;
				break;
			}
			case '<': {
				tileid = 12;
				break;
			}
			case '>': {
				tileid = 13;
				break;
			}
			case '?': {
				tileid = 14;
				break;
			}
			case '!': {
				tileid = 15;
				break;
			}
			case 't': {
				tileid = 11;
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


			sf::Vector2i tileCoords = sf::Vector2i(i, k);

			if (tileCoords.x > maxMapSize.x || tileCoords.y > maxMapSize.y) {
				std::cout << "! Tile is out of range: " << tileCoords.x << " " << tileCoords.y << std::endl;
				continue;
			}

			Tile tile;
			tile.properties = itr->second;
			if (tile.properties.id != 11)
				tile.teleport = false;
			else
				tile.teleport = true;

			if (!tileMap.emplace(GetTileIdByCoords(tileCoords.x, tileCoords.y), tile).second)
			{
				// Duplicate tile detected!
				std::cout << "! Duplicate tile! : " << tileCoords.x << " " << tileCoords.y << std::endl;
				continue;
			}
		}
		k++;
	}
	file.close();
}


void setSpawnPoint() {
	position = playerStartPoint;
	position.x = playerStartPoint.x * 32;
	position.y = playerStartPoint.y * 32;
	updateCollRect();
}
void SetEnemySpawnpoint(Nemico* ent) {
	ent->GetPos()->x = enemyStartPoint.x * 32;
	ent->GetPos()->y = enemyStartPoint.y * 32;
	ent->updateCollRect();
}
void CollisionEntity(Nemico* ent,std::vector<Nemico*>* entitiescollided) {
	unsigned int tileSize = 32;
	//ent->updateCollRect();
	int fromX = (int)floor(rectColl.left / tileSize); //rettangolo di collisione dell'entità parte sinistra
	int toX = (int)floor((rectColl.left + rectColl.width) / tileSize);//rettangolo di collisione dell'entità parte sinistra + larghezza
	int fromY = (int)floor(rectColl.top / tileSize);//rettangolo di collisione dell'entità parte in alto
	int toY = (int)floor((rectColl.top + rectColl.height) / tileSize);//rettangolo di collisione dell'entità parte in alto + altezza
	//( divido per il tilesize perché nei valori di top e height, width e left ci sono pixel )

	int fromXEnt = (int)floor(ent->GetCollRect().left / tileSize); //rettangolo di collisione dell'entità parte sinistra
	int toXEnt = (int)floor((ent->GetCollRect().left + ent->GetCollRect().width) / tileSize);//rettangolo di collisione dell'entità parte sinistra + larghezza
	int fromYEnt = (int)floor(ent->GetCollRect().top / tileSize);//rettangolo di collisione dell'entità parte in alto
	int toYEnt = (int)floor((ent->GetCollRect().top + ent->GetCollRect().height) / tileSize);//rettangolo di collisione dell'entità parte in alto + altezza
	//( divido per il tilesize perché nei valori di top e height, width e left ci sono pixel )
	// determino da che punto a che punto sull'asse delle x devo fare il controllo.
	// determino da che punto a che punto sull'asse delle y devo fare il controllo.
	//std::cout << "Player : " << fromXEnt << " " << toXEnt << " " << fromYEnt << " " << toYEnt << std::endl;
	//std::cout << "Enemy : " << fromX << " " << toX << " " << fromY << " " << toY << std::endl;
	for (int x = fromX; x <= toX; ++x) {
		for (int y = fromY; y <= toY; ++y) {

			if (x >= fromXEnt && x <= toXEnt) {
				if (y >= fromYEnt && y <= toYEnt) {
					sf::FloatRect tileBounds = sf::FloatRect(x * tileSize, y * tileSize, tileSize, tileSize);
					// ottengo i boundaries.
					sf::FloatRect intersection;
					sf::FloatRect intersectionEnt;
					rectColl.intersects(tileBounds, intersection);
					//questa funzione inserisce in "intersection" il valore di ritorno sull'intersezione.

					float area = intersection.width * intersection.height; //calcolo l'area d'intersezione.
					entitiescollided->push_back(ent);
				}
				else {
				}
			}
			else {
			}

		}
	}
	
}
bool ResolveCollisionEntity(char letter, std::vector<Nemico*> *entitiescollided) {
	unsigned int tileSize = 32;
		
		if (entitiescollided->size() == 0)return false;

		if(letter == 'f')
			return true;
		
		if (letter == 'r')
			return true;

		return false;
}