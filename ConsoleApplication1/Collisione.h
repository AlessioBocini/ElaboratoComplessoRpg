#pragma once
struct TileInfo;

struct CollisionElement {
	CollisionElement(float area, TileInfo* info,  sf::FloatRect bounds) : area(area) ,tilebounds(bounds), tile(info){
	}
	bool static SortCollisions(const CollisionElement& e_1, const CollisionElement & e_2) { 
		// funzione per ordinare in ordine crescente gli elementi collisi in base all'area
		return e_1.area > e_2.area;
	}
	float area; // l'area è quanto di quel tile stiamo collidendo
	TileInfo*  tile; // tile in questione
	sf::FloatRect tilebounds; //rettangolo delle boundaries.

};

using Collisions = std::vector<CollisionElement>; // typedef del vettore delle collisioni



