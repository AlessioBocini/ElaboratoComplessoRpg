#include "Entita.h"
#include "GameManager.h"
#include <iostream>
void Entita::CheckCollisions(SharedContext* context) {
	Mondo* world = context->gameMap;
	unsigned int tileSize = world->GetTileSize(); //ottengo la dimensione del tile = 32x32 => solo 32.

	int fromX = (int)floor(rectColl.left / tileSize); //rettangolo di collisione dell'entità parte sinistra
	int toX = (int)floor((rectColl.left + rectColl.width) / tileSize);//rettangolo di collisione dell'entità parte sinistra + larghezza
	int fromY = (int)floor(rectColl.top / tileSize);//rettangolo di collisione dell'entità parte in alto
	int toY = (int)floor((rectColl.top + rectColl.height) / tileSize);//rettangolo di collisione dell'entità parte in alto + altezza
	//( divido per il tilesize perché nei valori di top e height, width e left ci sono pixel )

	// determino da che punto a che punto sull'asse delle x devo fare il controllo.
	// determino da che punto a che punto sull'asse delle y devo fare il controllo.

	for (int x = fromX; x <= toX; ++x) {
		for (int y = fromY; y <= toY; ++y) {
			//faccio due for innestati, in quanto controllo tutte le coordinate in quell'area (e così i rispettivi tile).

			Tile* tile = world->GetTileByCoords(x, y); // ottengo il tile 


			if (!tile) continue; //se non esiste, skip
			if (!tile->properties->blocked && !tile->teleport)continue; //se non è bloccato e non è teletrasporto...skip
			//(in quanto significa che è un tile effettivo, ma non interessante)


			sf::FloatRect tileBounds = sf::FloatRect(x * tileSize, y * tileSize, tileSize, tileSize);
			// ottengo i boundaries.
			sf::FloatRect intersection;

			rectColl.intersects(tileBounds, intersection);
			//questa funzione inserisce in "intersection" il valore di ritorno sull'intersezione.

			float area = intersection.width * intersection.height; //calcolo l'area d'intersezione.
			CollisionElement e(area, tile->properties, tileBounds); //creo un nuovo CollisionElement.
			colls.emplace_back(e); //lo inserisco nelle collisioni avvenute.

			if (tile->teleport && entitytype == "Player") {
				//Se il tile è di teletrasporto esegue questa parte

				world->EraseMap(); //elimina la mappa attuale
				std::string lastMap = world->GetPrevMap(); //ottengo quale era la mappa precedente
				std::cout << tile->nextMap << std::endl;
				world->LoadMap(tile->nextMap, false);//carico la mappa successiva (definita nel tile colliso)
				world->SetPlayerStartpoint(tile->teleportPos);//definisco il nuovo spawnpoint 
				context->gameManager->SetPlayerStart(world->GetPlayerStartpoint()); // lo memorizzo anche nel gameManager
				world->SetPrevMap(tile->nextMap);//setto quale è la mappa precedente.

			}
		}
	}
}

void Entita::setSpawnPoint(sf::Vector2f pos) {
	position = pos;
	position.x = pos.x * 32;
	position.y = pos.y * 32;
	sprite.setPosition(pos.x * 32, pos.y * 32);
}
void Entita::ResolveCollisions(SharedContext* context) {
	isblockedA = false, isblockedD = false, isblockedS = false, isblockedW = false;

	//se ci sono state collissioni
	if (!colls.empty()) {
		std::sort(colls.begin(), colls.end(), CollisionElement::SortCollisions); //faccio il sort delle aree 
		// (una collisione dove l'intersezione è maggiore, ha più influenza e verrà applicata)
		Mondo* world = context->gameMap;
		unsigned int tileSize = world->GetTileSize();
		ResolveCollisionEntity(context);
		//si va a controllare e valutare cosa fare per ciascuna collissione
		for (auto& it : colls) {

			if (!rectColl.intersects(it.tilebounds)) {
				// diciamo è un caso di debug, nel quale nonostante si tratta di un caso di collissione con l'entità, 
				// il rettangolo di collisione dell'entità smette di collidere con i boundaries del tile
				// il che è fortemente improbabile.
				continue;
			}
			if (it.entity)
				continue;

			// da vicino l'entità all'estremo orizzontale - dall'estremo orizzontale a vinico il centro del tile (destra o sinistra dipende dal fatto che diffx sia > o < di 0)
			float diffx = (rectColl.left + (rectColl.width / 2)) - (it.tilebounds.left + (it.tilebounds.width / 2));
			// da vicino l'entità all'estremo verticale - dall'estremo verticale a vinico il centro del tile (alto o basso dipende dal fatto che diffx sia < o > di 0)
			float diffy = (rectColl.top + (rectColl.height / 2) - (it.tilebounds.top + (it.tilebounds.height / 2)));
			float resolve = 0;

			// è importante tuttavia reimpostare la posizione dell'entità nel momento in cui essa collide, al bordo corrispondente.
			//altrimenti rimane incastrata nel tile.
			//inoltre è evidente che se mi muovo orizzontalmente il diffy sarà sempre minore di diffx
			//stessa cosa ma viceversa se mi muovo verticalmente
			if (abs(diffx) > abs(diffy)) {
				if (diffx > 0) {
					//l'entità sta collidendo sulla destra.
					resolve = (it.tilebounds.left + tileSize) - rectColl.left; // il tileSize corrisponde al width del tileBound.
					// definisco la posizione corrispondente al bordo sinistro del tile
					isblockedD = true;
				}
				else {
					//altrimenti sta collidendo a sinistra.
					resolve = -((rectColl.left + rectColl.width) - it.tilebounds.left);
					// definisco la posizione corrispondente al bordo destro del tile
					isblockedA = true;
				}

				Movimento(resolve, 0); //sposto l'entità
			}
			else {
				if (diffy > 0) {
					//sta collidendo in basso.
					resolve = (it.tilebounds.top + tileSize) - rectColl.top;
					// definisco la posizione corrispondente al bordo in alto del tile 
					isblockedS = true;
				}
				else {
					//altrimenti sta collidendo in alto.
					resolve = -((rectColl.top + rectColl.height) - it.tilebounds.top);
					// definisco la posizione corrispondente al bordo in basso del tile
					isblockedW = true;
				}
				Movimento(0, resolve); //sposto l'entità
			}
		}
		colls.clear(); //elimino la collissione
	}

}
void Entita::CollisionEntity(Entita* ent, SharedContext* context) {
	Mondo* world = context->gameMap;
	unsigned int tileSize = world->GetTileSize(); //ottengo la dimensione del tile = 32x32 => solo 32.
	auto ps = ent;

	int fromX = (int)floor(rectColl.left / tileSize); //rettangolo di collisione dell'entità parte sinistra
	int toX = (int)floor((rectColl.left + rectColl.width) / tileSize);//rettangolo di collisione dell'entità parte sinistra + larghezza
	int fromY = (int)floor(rectColl.top / tileSize);//rettangolo di collisione dell'entità parte in alto
	int toY = (int)floor((rectColl.top + rectColl.height) / tileSize);//rettangolo di collisione dell'entità parte in alto + altezza
	//( divido per il tilesize perché nei valori di top e height, width e left ci sono pixel )

	int fromXEnt = (int)floor(ps->GetCollRect().left / tileSize); //rettangolo di collisione dell'entità parte sinistra
	int toXEnt = (int)floor((ps->GetCollRect().left + ps->GetCollRect().width) / tileSize);//rettangolo di collisione dell'entità parte sinistra + larghezza
	int fromYEnt = (int)floor(ps->GetCollRect().top / tileSize);//rettangolo di collisione dell'entità parte in alto
	int toYEnt = (int)floor((ps->GetCollRect().top + ps->GetCollRect().height) / tileSize);//rettangolo di collisione dell'entità parte in alto + altezza
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
					Tile* tile = new Tile();
					tile->properties = new TileInfo(context);
					tile->properties->blocked = true;
					CollisionElement e(area, tile->properties, tileBounds, true); //creo un nuovo CollisionElement.
					colls.emplace_back(e); //lo inserisco nelle collisioni avvenute.
					this->entitiescollided.push_back(ent);
				}
			}
		}
	}
}
void Entita::ResolveCollisionEntity(SharedContext* context) {
	Mondo* world = context->gameMap;
	unsigned int tileSize = world->GetTileSize();
	for (auto& it : colls) {
		if (!it.entity)
			continue;

		for(auto&ent: entitiescollided){
			//spostamento

				// da vicino l'entità all'estremo orizzontale - dall'estremo orizzontale a vinico il centro del tile (destra o sinistra dipende dal fatto che diffx sia > o < di 0)
			float diffx = (rectColl.left + (rectColl.width / 2)) - (it.tilebounds.left + (it.tilebounds.width / 2));
			// da vicino l'entità all'estremo verticale - dall'estremo verticale a vinico il centro del tile (alto o basso dipende dal fatto che diffx sia < o > di 0)
			float diffy = (rectColl.top + (rectColl.height / 2) - (it.tilebounds.top + (it.tilebounds.height / 2)));
			float segmentx = (ent->GetPosition().x - GetPosition().x)/tileSize;
			float segmenty = (ent->GetPosition().y - GetPosition().y)/tileSize;

			float resolve = 0;
			
			float resolverx = segmentx + (diffx / tileSize);
			float resolvery = segmenty - (diffy / tileSize);
			
			// è importante tuttavia reimpostare la posizione dell'entità nel momento in cui essa collide, al bordo corrispondente.
			//altrimenti rimane incastrata nel tile.
			//inoltre è evidente che se mi muovo orizzontalmente il diffy sarà sempre minore di diffx
			//stessa cosa ma viceversa se mi muovo verticalmente
				if (abs(diffx) > abs(diffy)) {

					if (this->D && resolverx > 0){
						//l'entità sta collidendo sulla destra.
						isblockedD = true;
					}
					else if (this->A && resolverx <= 0) {
						isblockedA = true;
					}
					else {
						//situazione strana + diagonale
					}
				}
				else {
					
					if (this->S && resolvery > 0) {
						isblockedS = true;
					}
					else if (this->W && resolvery <= 0) {//altrimenti verso l'alto.
						isblockedW = true;
					}
					else {
						//situazione strana + diagonale
					}
			}
		}
		entitiescollided.clear();
	}

}