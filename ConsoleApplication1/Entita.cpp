#include "Entita.h"
#include "GameManager.h"
#include <iostream>
void Entita::CheckCollisions(SharedContext* context) {
	Mondo* world = context->gameMap;
	unsigned int tileSize = world->GetTileSize();

	int fromX = floor(rectColl.left / tileSize);
	int toX = floor((rectColl.left + rectColl.width) / tileSize);
	int fromY = floor(rectColl.top / tileSize);
	int toY = floor((rectColl.top + rectColl.height) / tileSize);
	for (int x = fromX; x <= toX; ++x) {
		for (int y = fromY; y <= toY; ++y) {
			Tile* tile = world->GetTileByCoords(x, y);

			if (!tile) continue;
			if (!tile->properties->blocked)continue;
			sf::FloatRect tileBounds = sf::FloatRect(x * tileSize, y * tileSize, tileSize, tileSize);
			
			sf::FloatRect intersection;
			rectColl.intersects(tileBounds, intersection);
			float area = intersection.width * intersection.height;
			CollisionElement e(area, tile->properties, tileBounds);
			colls.emplace_back(e);
				/*if (tile->teleport && entitytype == "giocatore") {
					world->LoadNext()
				}*/

		}

	}
}


void Entita::ResolveCollisions(SharedContext* context) {
	isblockedA = false, isblockedD = false, isblockedS = false, isblockedW = false;
	if (!colls.empty()) {
		std::sort(colls.begin(),colls.end(),CollisionElement::SortCollisions);
		Mondo* world = context->gameMap;
		unsigned int tileSize = world->GetTileSize();
		for (auto& it : colls) {
			if (!rectColl.intersects(it.tilebounds)) {
				continue;
			}

			float diffx = (rectColl.left + (rectColl.width / 2)) - (it.tilebounds.left + (it.tilebounds.width / 2));
			float diffy = (rectColl.top + (rectColl.height / 2) - (it.tilebounds.top + (it.tilebounds.height / 2)));
			float resolve = 0;
			if (abs(diffx) > abs(diffy)) {
				if (diffx > 0) {
					resolve = (it.tilebounds.left + tileSize) - rectColl.left;
					isblockedD = true;
				}
				else {
					resolve = -((rectColl.left + rectColl.width) - it.tilebounds.left);
					isblockedA = false;
				}
				Movimento(resolve, 0);
				
				
			}
			else {
				if (diffy > 0) {
					resolve = (it.tilebounds.top + tileSize) - rectColl.top;
					isblockedS = true;
				}
				else {
					resolve = -((rectColl.top + rectColl.height) - it.tilebounds.top);
					isblockedW = true;
				}
				
				Movimento(0, resolve);
			}
			

		}
		
		colls.clear();
	}
	
}