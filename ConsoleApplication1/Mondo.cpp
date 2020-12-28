#include "Mondo.h"
Mondo::Mondo(SharedContext& context) :context(context), tileSetCount(0), lastMap(""), mappaCorrente(nullptr) {
	territori = std::vector<Territorio>();
	context.gameMap = this;
	LoadTiles("../assets/files/tiles.txt");
}

Mondo::~Mondo() {
	EraseWorld();
	
	context.gameMap = nullptr;
}

void Mondo::EraseWorld() {
	tileSet.clear();
	for (Territorio i : territori) {
		delete i.GetDecorationManager();
		i.EraseMap();
	}
	territori.clear();
}

void Mondo::EraseTileSet() {
	for (auto it = tileSet.begin(); it != tileSet.end(); it++)
		delete it->second;

	tileSetCount = 0;
}
Territorio Mondo::getActualMap() {
	return mappaCorrente;
}

TileSet* Mondo::GetTileSet()
{
	return &tileSet;
}

void Mondo::SetTileSet(TileSet* tileset)
{
	tileSet = *tileset;
}

void Mondo::Draw() {
	mappaCorrente.Draw();
}
unsigned int Mondo::GetTileSize() const {
	return Sheet::Tile_Size;
}
void Mondo::ChangeActualMap(std::string previous_map) {
	for (Territorio i : territori) {
		if (previous_map == i.GetCurrentTerritory()) {
			mappaCorrente = i;
		}
	}
}
void Mondo::LoadMaps() {
	
	std::vector<std::string> maps = {
		"shop","casa","guild","map1"
	};
	Territorio* t;
	for (unsigned int i = 0; i < maps.size()-1; i++) {
		t = new Territorio(&context);
		t->LoadMap(maps[i], false);
		territori.push_back(*t);
	}
	t = new Territorio(&context);
	t->LoadMap(maps[maps.size() - 1], true);
	territori.push_back(*t);
	
	mappaCorrente = *t;
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
		TileInfo* tile = new TileInfo(&context, texture, tileId);
		keystream >> tile->name >> tile->friction.x >> tile->friction.y >> tile->deadly >> tile->blocked;
		if (tileId == 1) {
			auto& animation = tile->anim.CreateAnimation("animationTerra", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationTerra");
		}
		else if (tileId == 3) {
			tile->sprite.setTextureRect(sf::IntRect(0, 0, Sheet::Tile_Size * 2, Sheet::Tile_Size * 2));
			auto& animation = tile->anim.CreateAnimation("animationPavimentoBlocked", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationPavimentoBlocked");
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
		else if (tileId == 11) {
			auto& animation = tile->anim.CreateAnimation("animationTeleport", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size * 6), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationTeleport");
		}
		else if (tileId == 12) {
			auto& animation = tile->anim.CreateAnimation("animationTerra", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, Sheet::Tile_Size), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationTerra");
		}
		else if (tileId == 13) {
			auto& animation = tile->anim.CreateAnimation("animationwater", texture, sf::seconds(1), true);
			animation.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(Sheet::Tile_Size, Sheet::Tile_Size), 1);
			tile->animation.push_back(animation);
			tile->anim.SwitchAnimation("animationwater");
		}
		if (!tileSet.emplace(tileId, tile).second) {
			// Duplicate tile detected!
			std::cout << "! Duplicate tile type: " << tile->name << std::endl;
			delete tile;
		}
	}
	file.close();
}

std::string Mondo::GetPrevMap() {
	return lastMap;
}
void Mondo::SetPrevMap(std::string previous_map) {
	lastMap = previous_map;
}