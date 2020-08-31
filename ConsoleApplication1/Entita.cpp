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
			if (!tile->properties->blocked && !tile->teleport )continue; //se non è bloccato e non è teletrasporto...skip
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
					
					world->LoadMap(tile->nextMap,false);//carico la mappa successiva (definita nel tile colliso)
					sf::Vector2f pos = world->GetPlayerStartpoint(); //ottengo lo spawn point del giocatore in quella mappa

					if (lastMap == "map1" && tile->nextMap == "casa") {
						pos.y--;
					}
					else if (lastMap == "casa" && tile->nextMap == "map1") {
						pos.y++;
					}

					world->SetPlayerStartpoint(pos);//definisco il nuovo spawnpoint 
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
		std::sort(colls.begin(),colls.end(),CollisionElement::SortCollisions); //faccio il sort delle aree 
		// (una collisione dove l'intersezione è maggiore, ha più influenza e verrà applicata)
		Mondo* world = context->gameMap;
		unsigned int tileSize = world->GetTileSize();

		//si va a controllare e valutare cosa fare per ciascuna collissione
		for (auto& it : colls) {

			if (!rectColl.intersects(it.tilebounds)) { 
				// diciamo è un caso di debug, nel quale nonostante si tratta di un caso di collissione con l'entità, 
				// il rettangolo di collisione dell'entità smette di collidere con i boundaries del tile
				// il che è fortemente improbabile.
				continue;
			}

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
					resolve = (it.tilebounds.left + tileSize ) - rectColl.left; // il tileSize corrisponde al width del tileBound.
					// definisco la posizione corrispondente al bordo sinistro del tile
					isblockedD = true; 
				}
				else {
					//altrimenti sta collidendo a sinistra.
					resolve = -((rectColl.left + rectColl.width) - it.tilebounds.left);
					// definisco la posizione corrispondente al bordo destro del tile
					isblockedA = false;
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