#include "Mondo.h"
#include "GameManager.h"
#include <iostream>
Mondo::Mondo(SharedContext* context) :context(context), tileCount(0), tileSetCount(0), maxMapSize(400, 200), lastMap("") {
	context->gameMap = this;
	LoadTiles("D:/visualstudioprojects/consoleApp/assets/files/tiles.txt");
}
Mondo::~Mondo() {
	EraseTileSet();
	EraseMap();
	context->gameMap = nullptr;
}


Tile* Mondo::GetTileByCoords(int x, int y) {

	auto id = GetTileIdByCoords(x, y);
	auto itr = tileMap.find(id);
	return (itr != tileMap.end()) ? itr->second : nullptr;
}


TileId Mondo::GetTileIdByCoords(int x, int y) {
	return (x * maxMapSize.x) + y;
}

void Mondo::EraseMap() {
	/*for (auto it = tileMap.begin(); it != tileMap.end(); it++) {
		delete it->second;
	}*/

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
void Mondo::SetPlayerStartpoint(const sf::Vector2f& newpos) {
	playerStartPoint = newpos;
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
		keystream >> tileId >> texture;
		if (tileId < 0) { continue; }
		TileInfo* tile = new TileInfo(context, texture, tileId);
		keystream >> tile->name >> tile->friction.x >> tile->friction.y >> tile->deadly >> tile->blocked;
		if (tileId == 1) {
			auto& animation = tile->anim.CreateAnimation("animationTerra", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationTerra");
		}
		else if (tileId == 3) {
			tile->sprite.setTextureRect(sf::IntRect(0, 0, Sheet::Tile_Size * 2, Sheet::Tile_Size * 2));
			auto& animation = tile->anim.CreateAnimation("animationAcquaGrande", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size), sf::Vector2i(Sheet::Tile_Size * 2, Sheet::Tile_Size * 2), 3);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationAcquaGrande");
		}
		else if (tileId == 2) {
			auto& animation = tile->anim.CreateAnimation("animationStradapiccola", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(Sheet::Tile_Size * 3, 0), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationStradapiccola");

		}
		else if (tileId == 4) {
			auto& animation = tile->anim.CreateAnimation("animationMuro", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size * 2), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationMuro");
		}
		else if (tileId == 5) {
			auto& animation = tile->anim.CreateAnimation("animationCespuglio", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationCespuglio");
		}
		else if (tileId == 9) {
			auto& animation = tile->anim.CreateAnimation("animationMuroCasa", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size * 2), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationMuroCasa");
		}
		else if (tileId == 10) {
			auto& animation = tile->anim.CreateAnimation("animationPavimentoCasa", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationPavimentoCasa");
		}
		else if (tileId == 11) { //letto
			auto& animation = tile->anim.CreateAnimation("animationLetto", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size * 4), sf::Vector2i(Sheet::Tile_Size * 2, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationLetto");
		}
		else if (tileId == 12) { //sedia1 <
			auto& animation = tile->anim.CreateAnimation("animationSedia1", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size * 3), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationSedia1");
		}
		else if (tileId == 13) { //sedia2 >
			auto& animation = tile->anim.CreateAnimation("animationSedia2", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(Sheet::Tile_Size * 2, Sheet::Tile_Size * 3), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationSedia2");
		}
		else if (tileId == 14) { // tavolo
			auto& animation = tile->anim.CreateAnimation("animationTavolino", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size * 3), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationTavolino");

		}
		else if (tileId == 15) { 
			auto& animation = tile->anim.CreateAnimation("animationScrivania", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(Sheet::Tile_Size * 4, Sheet::Tile_Size * 4), sf::Vector2i(Sheet::Tile_Size * 2, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationScrivania");
		}
		else if (tileId == 16) {
			auto& animation = tile->anim.CreateAnimation("animationTeleport", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size * 6), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationTeleport");
		}
		else if (tileId == 17) {
			auto& animation = tile->anim.CreateAnimation("animationCasa", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(Sheet::Tile_Size * 3, Sheet::Tile_Size * 3), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationCasa");
		}
		else if (tileId == 18) {
			//scrivania verticale
			auto& animation = tile->anim.CreateAnimation("animationScrivaniaVerticale", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size * 9), sf::Vector2i(Sheet::Tile_Size , Sheet::Tile_Size*3), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationScrivaniaVerticale");
		}
		else if (tileId == 19) {
			auto& animation = tile->anim.CreateAnimation("animationScrivaniaVenditore", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size * 11), sf::Vector2i(Sheet::Tile_Size * 3, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationScrivaniaVenditore");
		}
		if (!tileSet.emplace(tileId, tile).second) {
			// Duplicate tile detected!
			std::cout << "! Duplicate tile type: " << tile->name << std::endl;
			delete tile;
		}
	}
	file.close();
}
void Mondo::LoadMap(const std::string& filepath, bool first) {
	/*
	T = terra
	t = teleport
	S0 = strada Grande TODO
	00

	s = strada piccola

	A0 = Acqua grande
	00

	a = acqua piccola TODO
	P = Player
	N = Nemico1 17
	n = npc 
	# = muro

	c = cespuglio

	F0 = foresta grande TODO
	00

	f0 = albero TODO
	00

	m = muro casa
	m = casa se in mappe diverse da Casa.
	p = pavimento casa

	< = sedia 1
	> = sedia 2
	? = tavolo
	! = scrivania
	l = letto
	*/
	std::string path = "D:/visualstudioprojects/consoleApp/assets/files/";
	std::string postfix = ".map";
	std::ifstream file;
	int teleportcounter = 0;
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
			case 'N': {
				//coming soon.
				break;
			}
			case 'n': {
				if (filepath == "casa" || filepath == "shop") {
					

					context->entityManager->Add(EntityType::Shopkeeper, "Shopkeeper");
					context->entityManager->getNpcs().back()->setMap(filepath);
					context->entityManager->getNpcs().back()->setSpawnPoint(sf::Vector2f(i,k));
					tileid = 10;
				}
				else if (filepath == "map1") {
					tileid = 1;
				}
				break;
			}
			case 'P': {
				if (filepath == "casa"||filepath=="shop")
					tileid = 10;
				else if (filepath == "map1") {
					tileid = 1;
					SetPlayerStartpoint(sf::Vector2f(i, k));
				}

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
				if (filepath == "shop")
					tileid = 18;
				break;
			}
			case 'm': {
				tileid = 17;
				if (filepath == "casa"||filepath=="shop")
					tileid = 9;
				
					
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
				tileid = 19;
				if (filepath == "casa")
					tileid = 15;
				
					
				break;
			}
			case 't': {
				tileid = 16;
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

			Tile* tile = new Tile();
			tile->properties = itr->second;
			tile->teleport = false;
			if (16 == tileid) {
				if (filepath == "casa") {
					tile->teleport = true;
					tile->nextMap = "map1";
					tile->teleportPos = sf::Vector2f(30, 5);
				}
				if (filepath == "shop") {
					tile->teleport = true;
					tile->nextMap = "map1";
					tile->teleportPos = sf::Vector2f(11, 12);
				}
				if (filepath == "map1") {
					tile->teleport = true;
					
					if (teleportcounter == 0) {
						tile->nextMap = "casa";
						tile->teleportPos = sf::Vector2f(8, 8);
					}
					if (teleportcounter == 1) {
						tile->nextMap = "shop";
					    tile->teleportPos = sf::Vector2f(2, 3);
					}	
					if (teleportcounter == 2)
						tile->nextMap = "guild";
					if (teleportcounter == 3)
						tile->nextMap = "casa2";

					teleportcounter++;
				}
				
			}

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

std::string Mondo::GetPrevMap() {
	return lastMap;
}
void Mondo::SetPrevMap(std::string previous_map) {
	lastMap = previous_map;
}
void Mondo::Update(sf::Time const& dt) {
	for (auto it : tileMap) {
		it.second->properties->anim.update(dt);
	}

}
void Mondo::Draw() {
	sf::RenderWindow* wind = context->wind->GetRenderWindow();
	sf::FloatRect viewSpace = context->wind->GetViewSpace(); // ottengo il rettangolo visibile.
	//ottengo l'insieme dei tile (iniziali e finali) visibili entro la finestra del rettangolo visibile.
	sf::Vector2i tileBegin(floor(viewSpace.left / Sheet::Tile_Size), floor(viewSpace.top / Sheet::Tile_Size)); //dimensioni finestra visibile in coordinate sinistra e top, per difetto
	sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size), ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size)); //dimensioni finestra visibile in coordinate sinistra + larghezza e top + altezza, per eccesso.
	//( sempre diviso il tileSize per ottenere i tile, e non i pixel ).
	unsigned int count = 0;
	// l'unica cosa cambiata in questo for-loop è il fatto che ora il display è fatto usando tileBegin e tileEnd di viewSpace,
	// prima infatti tileBegin e tileEnd si ottenevano dalla finestra/mappa completa di gioco, e non una sua porzione visibile.
	for (int x = tileBegin.x - 5; x <= tileEnd.x +5; ++x) {
		for (int y = tileBegin.y -5; y <= tileEnd.y + 5; ++y) {
			if (x < 0 || y < 0) { continue; }
			Tile* tile = GetTileByCoords(x, y);
			if (!tile) { continue; }
			sf::Sprite& sprite = tile->properties->sprite;
			sprite.setPosition((float)x * Sheet::Tile_Size, (float)y * Sheet::Tile_Size);
			wind->draw(sprite);
			++count;
		}
	}
}
