#pragma once
struct TileInfo;

struct CollisionElement {
	CollisionElement(float area, TileInfo* info,  sf::FloatRect bounds) : area(area) ,tilebounds(bounds), tile(info){
	}
	bool static SortCollisions(const CollisionElement& e_1, const CollisionElement & e_2) {
		return e_1.area > e_2.area;
	}
	float area;
	TileInfo*  tile;
	sf::FloatRect tilebounds;

};

using Collisions = std::vector<CollisionElement>;



