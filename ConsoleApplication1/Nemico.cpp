#include "Nemico.h"
#include "Mondo.h"

void Nemico::Movimento(float x, float y) {
	oldPosition = position;
	position += sf::Vector2f(x, y);
	A = false, D = false, S = false, W = false;
	if (x > 0)
		D = true;
	else if (x < 0)
		A = true;

	if (y > 0)
		S = true;
	else if (y < 0)
		W = true;

	sprite.move(x, y);

	updateCollRect(); //aggiorna le informazioni sulle collisioni
}
void Nemico::Attacco(bool isSkill) {

}
/*
void Nemico::CollisionEntity(Giocatore* ent, SharedContext* context) {
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

					rectColl.intersects(tileBounds, intersection);
					//questa funzione inserisce in "intersection" il valore di ritorno sull'intersezione.

					float area = intersection.width * intersection.height; //calcolo l'area d'intersezione.

					Tile* tile = new Tile();
					tile->properties = new TileInfo(context);
					tile->properties->blocked = true;
					CollisionElement e(area, tile->properties, tileBounds); //creo un nuovo CollisionElement.
					colls.emplace_back(e); //lo inserisco nelle collisioni avvenute.
				}
			}
		}

	}

}*/
