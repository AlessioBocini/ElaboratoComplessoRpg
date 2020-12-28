#include "Territorio.h"
#include "GameManager.h"
#include <iostream>
Territorio::Territorio(SharedContext* context):maxMapSize(400, 200), tileCount(0),context(context) , propretario(-1), loadNextMap(""), currentState(NULL),deco(new DecorationManager(context)){}

Territorio::~Territorio() {}

Tile* Territorio::GetTileByCoords(int x, int y) {

	TileId id = GetTileIdByCoords(x, y);
	auto itr = tileMap.find(id);
	return (itr != tileMap.end()) ? itr->second : nullptr;
}

std::string Territorio::GetCurrentTerritory()
{
	return currentTerritory;
}

void Territorio::SetCurrentTerritory(const std::string& territory)
{
	currentTerritory = territory;
}

Arredamento* Territorio::GetDecorationByCoords(int x, int y)
{
	return deco->GetArredamentoByCoords(x,y);
}

DecorationManager* Territorio::GetDecorationManager()
{
	return deco;
}



TileId Territorio::GetTileIdByCoords(int x, int y) {
	return (x * maxMapSize.x) + y;
}


void Territorio::EraseMap() {
	

	tileCount = 0;
	for (auto it = tileMap.begin(); it != tileMap.end(); it++) {
		delete it->second;
	}
	tileMap.clear();
	
}

const sf::Vector2f& Territorio::GetPlayerStartpoint() const {

	return playerStartPoint;
}
void Territorio::SetPlayerStartpoint(const sf::Vector2f& newpos) {
	playerStartPoint = newpos;
}
const sf::Vector2u& Territorio::GetMapSize() const {
	return maxMapSize;
}


void Territorio::LoadMap(const std::string& filepath, bool first) {
	currentTerritory = filepath;

	std::string path = "../assets/files/"+filepath+"/";
	std::string postfix = ".map";
	std::ifstream file;
	int teleportcounter = 0;
	file.open(path + filepath + postfix);
	if (!file.is_open()) { std::cout << "! Failed loading map file: " << filepath << std::endl; return; }
	std::string map;
	char letter = '.';
	bool isEntity = false;
	int k = 0, i = 0, tipo = 0;
	while (!file.eof()) {
		
		
		i = 0;
		do{
			file >> letter;
			if (letter != '.') {
				isEntity = false;
				TileId tileid;

				switch (letter)
				{
				case '#': {
					tileid = 4;
					break;
				}
				case 'N': {
					file >> tipo;
					switch (tipo)
					{
					case 0: {
						context->entityManager->Add(EntityType::Enemy, "Scheletro", filepath, int(EnemyType::Skeleton));
						break;
					}
					case 1: {
						context->entityManager->Add(EntityType::Enemy, "Cristallo", filepath, int(EnemyType::Crystal));
						break;
					}
					case 2: {
						context->entityManager->Add(EntityType::Enemy, "Bandito", filepath, int(EnemyType::Bandit));
						break;
					}
					default:
						break;
					}
					context->entityManager->getEntities().back()->setSpawnPoint(sf::Vector2f(i, k));
					break;
				}
				case 'n': {


					file >> tipo;
					switch (tipo)
					{
					case 0: {
						context->entityManager->Add(EntityType::NPC, "Shopkeeper", filepath, int(NpcType::Shopkeeper));
						break;
					}
					case 1: {
						context->entityManager->Add(EntityType::NPC, "Guardia", filepath, int(NpcType::Guard));
						break;
					}

					default:
						break;
					}
					context->entityManager->getEntities().back()->setSpawnPoint(sf::Vector2f(i, k));


					if (filepath == "map1") {
						tileid = 1;
					}
					else {
						tileid = 10;
					}
					break;
				}
				case 'P': {

					if (filepath == "map1") {
						tileid = 1;
					}
					else {
						tileid = 10;
					}
					SetPlayerStartpoint(sf::Vector2f(i, k));
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
				case 'A': {//arredamento
					file >> tipo;
					switch (tipo)
					{
					case 0: { //laghetto
						deco->AddArredamento("laghetto", filepath, sf::Vector2f(i, k));
						tileid = 13;
						break;
					}
					case 1: { //lago grande
						deco->AddArredamento("lago grande", filepath, sf::Vector2f(i, k));
						tileid = 13;
						break;
					}
					case 2: {//porta
						deco->AddArredamento("porta", filepath, sf::Vector2f(i, k));
						tileid = 6;
						break;
					}
					case 3: { //casa
						deco->AddArredamento("casa", filepath, sf::Vector2f(i, k));
						tileid = 12;
						break;
					}
					case 4: { //sedia >
						deco->AddArredamento("sedia >", filepath, sf::Vector2f(i, k));
						tileid = 3;
						break;
					}
					case 5: { //sedia <
						deco->AddArredamento("sedia <", filepath, sf::Vector2f(i, k));
						tileid = 3;
						break;
					}
					case 6: { //tavolo
						deco->AddArredamento("tavolino", filepath, sf::Vector2f(i, k));
						tileid = 3;
						break;
					}
					case 7: { //scrivania
						deco->AddArredamento("scrivania", filepath, sf::Vector2f(i, k));
						tileid = 3;
						break;
					}
					case 8: { //letto orizzontale
						deco->AddArredamento("letto orizzontale", filepath, sf::Vector2f(i, k));
						tileid = 3;
						break;
					}
					case 9: { //scrivania
						deco->AddArredamento("scrivania verticale", filepath, sf::Vector2f(i, k));
						tileid = 3;
						break;
					}
					case 10: { //letto verticale
						deco->AddArredamento("letto verticale", filepath, sf::Vector2f(i, k));
						tileid = 3;
						break;
					}
					case 11: {
						deco->AddArredamento("fiori", filepath, sf::Vector2f(i, k));
						tileid = 1;
						break;
					}
					case 12: {
						deco->AddArredamento("erba", filepath, sf::Vector2f(i, k));
						tileid = 1;
						break;
					}
					case 13: {
						deco->AddArredamento("roccia grande", filepath, sf::Vector2f(i, k));
						break;
					}
					case 14: {
						deco->AddArredamento("ciottoli", filepath, sf::Vector2f(i, k));
						break;
					}

					default:
						break;
					}
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
				case '4': { //blocked pavimento casa
					tileid = 3;
					break;
				}
				case '5': { //blocked erba
					tileid = 12;
					break;
				}
				case 'c': {
					tileid = 5;
					break;
				}
				case 'm': {
					tileid = 9;
					break;
				}
				case 'p': {
					tileid = 10;
					break;
				}
				case 't': {	
					tileid = 11;
					if (filepath == "map1") {
						tileid = 2;
					}

				
					break;
				}
				case 'w': {
					tileid = 13;
					break;
				}

				default: {
					std::cout << "error occurred" << std::endl;
					break;
				}
				}
				auto itr = context->gameMap->GetTileSet()->find(tileid);


				if (itr == context->gameMap->GetTileSet()->end())
					continue;


				sf::Vector2i tileCoords = sf::Vector2i(i, k);

				if (tileCoords.x > int(maxMapSize.x) || tileCoords.y > int(maxMapSize.y)) {
					std::cout << "! Tile is out of range: " << tileCoords.x << " " << tileCoords.y << std::endl;
					continue;
				}

				Tile* tile = new Tile();
				tile->properties = itr->second;
				tile->teleport = false;
				if ('t'==letter) {
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
					if (filepath == "guild") {
						tile->teleport = true;
						tile->nextMap = "map1";
						tile->teleportPos = sf::Vector2f(16, 12);
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
						if (teleportcounter == 2) {
							tile->nextMap = "guild";
							tile->teleportPos = sf::Vector2f(2, 3);
						}
						if (teleportcounter == 3)
							tile->nextMap = "casa2";

						tile->doorPos = new sf::Vector2f(i, k-1);
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
			i++;
			
			
		}while (letter != '.');
		k++;
	}
	file.close();


}


void Territorio::Update(sf::Time const& dt) {
	for (auto it : tileMap) {
		it.second->properties->anim.update(dt);
	}
	
	deco->Update(dt);
	
		
}

void Territorio::Draw() {
	sf::RenderWindow* wind = context->wind->GetRenderWindow();
	sf::FloatRect viewSpace = context->wind->GetViewSpace(); // ottengo il rettangolo visibile.
	//ottengo l'insieme dei tile (iniziali e finali) visibili entro la finestra del rettangolo visibile.
	sf::Vector2i tileBegin(floor(viewSpace.left / Sheet::Tile_Size), floor(viewSpace.top / Sheet::Tile_Size)); //dimensioni finestra visibile in coordinate sinistra e top, per difetto
	sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size), ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size)); //dimensioni finestra visibile in coordinate sinistra + larghezza e top + altezza, per eccesso.
	//( sempre diviso il tileSize per ottenere i tile, e non i pixel ).
	unsigned int count = 0;
	// l'unica cosa cambiata in questo for-loop è il fatto che ora il display è fatto usando tileBegin e tileEnd di viewSpace,
	// prima infatti tileBegin e tileEnd si ottenevano dalla finestra/mappa completa di gioco, e non una sua porzione visibile.
	for (int x = tileBegin.x ; x <= tileEnd.x; ++x) {
		for (int y = tileBegin.y; y <= tileEnd.y; ++y) {
			if (x < 0 || y < 0) { continue; }

			Tile* tile = GetTileByCoords(x, y);
			if (!tile) { continue; }
			sf::Sprite& sprite = tile->properties->sprite;
			sprite.setPosition((float)x * Sheet::Tile_Size, (float)y * Sheet::Tile_Size);
			wind->draw(sprite);
			++count;
		}
	}

	deco->Draw();
}

