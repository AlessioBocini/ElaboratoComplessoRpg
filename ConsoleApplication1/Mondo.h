#pragma once

#include "Territorio.h"


class Mondo {
private:
	
	void LoadTiles(const std::string& path);
	
	std::string lastMap;


	unsigned int tileSetCount;
	
	void EraseTileSet();
	SharedContext& context;
	std::vector<Territorio> territori;
	Territorio mappaCorrente;
	TileSet tileSet;
public:
	Mondo(SharedContext& context);
	~Mondo();
	unsigned int GetTileSize() const;
	
	void LoadMaps();
	void EraseWorld();
	std::string GetPrevMap();
	void SetPrevMap(std::string previous_map);
	void ChangeActualMap(std::string previous_map);
	Territorio getActualMap();
	TileSet* GetTileSet();
	void SetTileSet(TileSet* tileset);
	void Draw();
	int GetNTerritori() {
		return this->territori.size();
	}
};