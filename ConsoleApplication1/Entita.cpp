#include "Entita.h"
#include "GameManager.h"
#include <iostream>
void Entita::CheckCollisions(/*SharedContext* context*/) {
	Mondo* world = context.gameMap;
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

			Tile* tile = world->getActualMap().GetTileByCoords(x, y); // ottengo il tile 


			if (!tile) continue; //se non esiste, skip
			if (!tile->properties->blocked && !tile->teleport)continue; //se non è bloccato e non è teletrasporto...skip
			//(in quanto significa che è un tile effettivo, ma non interessante)

			if (tile->teleport && entitytype == "Player") {
				//Se il tile è di teletrasporto esegue questa parte
				if (Interacting) {
	
					sf::Clock clock = sf::Clock();
					if (tile->doorPos != nullptr) {
						float posx = tile->doorPos->x,
							  posy = tile->doorPos->y;

						Arredamento* decoration = world->getActualMap().GetDecorationByCoords(posx, posy);
						if (decoration != nullptr) { 
							Animator* decoAnimpg = decoration->GetAnimpg();
							decoAnimpg->SwitchAnimation("animation1");
							decoration->PrepareTeleport(tile);
						}
						else {
							//caso di debug
							std::cout << "Errore! - ho coordinate porta, non ho la porta" << std::endl;
							// è impossibile che non ci sia la porta se ho le sue coordinate
						}
					}
					else {
						context.gameManager->SetPlayerStart(tile->teleportPos);
						world->SetPrevMap(tile->nextMap);//setto quale è la mappa precedente.
						world->ChangeActualMap(tile->nextMap);
						world->getActualMap().SetPlayerStartpoint(tile->teleportPos);//definisco il nuovo spawnpoint
					}
					
					
				}
			}
			else {
				sf::FloatRect tileBounds = sf::FloatRect(x * tileSize, y * tileSize, tileSize, tileSize);
				// ottengo i boundaries.
				sf::FloatRect intersection;

				rectColl.intersects(tileBounds, intersection);
				//questa funzione inserisce in "intersection" il valore di ritorno sull'intersezione.

				float area = intersection.width * intersection.height; //calcolo l'area d'intersezione.
				CollisionElement e(area, tile->properties, tileBounds); //creo un nuovo CollisionElement.
				colls.emplace_back(e); //lo inserisco nelle collisioni avvenute.
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
void Entita::ResolveCollisions(/*SharedContext* context*/) {
	isblockedA = false, isblockedD = false, isblockedS = false, isblockedW = false;

	//se ci sono state collissioni
	if (!colls.empty()) {
		std::sort(colls.begin(), colls.end(), CollisionElement::SortCollisions); //faccio il sort delle aree 
		// (una collisione dove l'intersezione è maggiore, ha più influenza e verrà applicata)
		Mondo* world = context.gameMap;
		unsigned int tileSize = world->GetTileSize();
		ResolveCollisionEntity(/*context*/);
		
		//si va a controllare e valutare cosa fare per ciascuna collissione

		for (CollisionElement& it : colls) {

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
					if (entitytype == "Nemico1") {
						animpg.SwitchAnimation("animationD");
					}
				}
				else {
					//altrimenti sta collidendo a sinistra.
					resolve = -((rectColl.left + rectColl.width) - it.tilebounds.left);
					// definisco la posizione corrispondente al bordo destro del tile
					isblockedA = true;
					if (entitytype == "Nemico1") {
						animpg.SwitchAnimation("animationA");
					}
				}
				Movimento(resolve, 0); //sposto l'entità
			}
			else {
				if (diffy > 0) {
					//sta collidendo in basso.
					resolve = (it.tilebounds.top + tileSize) - rectColl.top;
					// definisco la posizione corrispondente al bordo in alto del tile 
					isblockedS = true;

					if (entitytype == "Nemico1") {
						animpg.SwitchAnimation("animationS");
					}
				}
				else {
					//altrimenti sta collidendo in alto.
					resolve = -((rectColl.top + rectColl.height) - it.tilebounds.top);
					// definisco la posizione corrispondente al bordo in basso del tile
					isblockedW = true;
					if (entitytype == "Nemico1") {
						animpg.SwitchAnimation("animationW");
					}
				}
				Movimento(0, resolve); //sposto l'entità
			}
		}
		colls.clear(); //elimino la collissione
	}
	Attacking = false, Interacting = false;
}
void Entita::CollisionEntity(Entita* ent/*, SharedContext* context*/) {
	Mondo* world = context.gameMap;
	unsigned int tileSize = world->GetTileSize(); //ottengo la dimensione del tile = 32x32 => solo 32.

	int fromX = (int)floor(rectColl.left / tileSize); //rettangolo di collisione dell'entità parte sinistra
	int toX = (int)floor((rectColl.left + rectColl.width) / tileSize);//rettangolo di collisione dell'entità parte sinistra + larghezza
	int fromY = (int)floor(rectColl.top / tileSize);//rettangolo di collisione dell'entità parte in alto
	int toY = (int)floor((rectColl.top + rectColl.height) / tileSize);//rettangolo di collisione dell'entità parte in alto + altezza
	//( divido per il tilesize perché nei valori di top e height, width e left ci sono pixel )

	int fromXEnt = (int)floor(ent->GetCollRect().left / tileSize); //rettangolo di collisione dell'entità parte sinistra
	int toXEnt = (int)floor((ent->GetCollRect().left + ent->GetCollRect().width) / tileSize);//rettangolo di collisione dell'entità parte sinistra + larghezza
	int fromYEnt = (int)floor(ent->GetCollRect().top / tileSize);//rettangolo di collisione dell'entità parte in alto
	int toYEnt = (int)floor((ent->GetCollRect().top + ent->GetCollRect().height) / tileSize);//rettangolo di collisione dell'entità parte in alto + altezza
	//( divido per il tilesize perché nei valori di top e height, width e left ci sono pixel )
	// determino da che punto a che punto sull'asse delle x devo fare il controllo.
	// determino da che punto a che punto sull'asse delle y devo fare il controllo.
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
					tile->properties = new TileInfo(&context);
					tile->properties->blocked = true;
					CollisionElement e(area, tile->properties, tileBounds, true); //creo un nuovo CollisionElement.
					colls.emplace_back(e); //lo inserisco nelle collisioni avvenute.
					this->entitiescollided.push_back(ent);// aggiungo ent alle entità collise
				}
				else {
				}
			}
			else {
			}
			
		}
	}
}
void Entita::ResolveCollisionEntity(/*SharedContext* context*/) {
	Mondo* world = context.gameMap;
	unsigned int tileSize = world->GetTileSize();

	sf::Vector2f thisPosition = GetSprite().getPosition();
	for (CollisionElement& it : colls) { //controllo tutte le collisioni
		if (!it.entity) //se è
			continue;

		for(Entita* &ent: entitiescollided){
			//spostamento

			sf::Vector2f entPos = ent->GetSprite().getPosition();
			float segmentx = (entPos.x - thisPosition.x)/tileSize;  //distanza tra ent e questa entità asse X
			float segmenty = (entPos.y - thisPosition.y)/tileSize; //distanza tra ent e questa entità asse Y
	
			if (Attacking) {

				sf::Time elapsed = clockAttack.getElapsedTime();

				if (elapsed.asSeconds() > cooldownAutoAttack) {

					if (segmentx > 0 && this->lastDirection == 'D') { 
						//caso in cui il nemico è alla mia destra e mi muovo a destra
						if (Attacco(ent, SkillAttack)) {
						}
						clockAttack.restart();
					}
					else if (segmentx <= 0 && this->lastDirection == 'A') {
						//caso in cui il nemico è alla mia sinistra e mi muovo a sinistra
						if (Attacco(ent, SkillAttack)) {
						}
						clockAttack.restart();
					}
					else if (segmenty > 0 && this->lastDirection == 'S') {
						//caso in cui il nemico è a sud e mi muovo in basso
						if (Attacco(ent, SkillAttack)) {
						}
						clockAttack.restart();
					}
					else if (segmenty <= 0 && this->lastDirection == 'W') {
						//caso in cui il nemico è a nord e mi muovo in alto
						if (Attacco(ent, SkillAttack)) {
						}
						clockAttack.restart();
					}
				}
				

				
			}
			
			if (Interacting) {
			Giocatore* x = dynamic_cast<Giocatore*>(this);
				if (x != nullptr) {
					x->Interazione(*ent); //attivo l'interazione di questo tipo di entità (player)
				}
			}

			//casi ulteriori (blocco movimento):
			if (this->D && segmentx > 0 && Touchable(segmenty)){ 
				//l'entità sta collidendo alla mia destra e mi muovo a destra (ed è toccabile).
				isblockedD = true;
			}
			else if (this->A && segmentx <= 0 && Touchable(segmenty)) {
				//l'entità sta collidendo alla mia sinistra e mi muovo a sinistra (ed è toccabile).
				isblockedA = true;
			}
			else {
			}
				
					
			if (this->S && segmenty > 0) { 
				//verso basso
				isblockedS = true;
			}
			else if (this->W && segmenty <= 0) {
				//altrimenti verso l'alto.
				isblockedW = true;
			}
			else {
			}


				
			
		}
		entitiescollided.clear();
	}

}

void Entita::Update(sf::Time const& dt) {
	animpg.update(dt);
	updateCollRect();
	
	if (GetVitalita() < GetMaxVitalita())
		RegenHitPoints();

	Giocatore* ps = dynamic_cast<Giocatore*>(this);
	if (ps != nullptr) {

		if(ps->GetStamina() < ps->GetMaxStamina())
			ps->RegenStamina();
	}
}
Animator* Entita::GetAnimpg()
{
	return &animpg;
}
std::vector<AnimSet> Entita::GetAnimations()
{
	return animations;
}
Inventario* Entita::GetInventario()
{
	return &inventario;
}
void Entita::SetMaxVitalita(int vit) {
	this->maxvitalita = vit;
}
int Entita::GetMaxVitalita() {
	return this->maxvitalita;
}

void Entita::SetLastDirection(char newDirection) {
	this->lastDirection = newDirection;
}
char Entita::GetLastDirection() {
	return lastDirection;
}
std::string Entita::GetNome() {
	return nome;
}
void Entita::SetNome(std::string newnome) {
	this->nome = newnome;
}
int Entita::GetVitalita() {
	return this->vitalita;
}
void Entita::SetVitalita(int vit) {
	this->vitalita = vit;
}
float  Entita::GetVelocita() {
	return velocita/100;
}
void Entita::SetVelocita(float vel) {
	velocita = vel;
}
int Entita::GetForza() {
	return forza;
}
void Entita::SetForza(int const& forza) {
	this->forza = forza;
}
int Entita::GetLivello() {
	return livello;
}
void Entita::SetLivello(int const& liv) {
	livello = liv;
}

sf::Vector2f Entita::GetPosition() {
	return position;
}
void Entita::SetPosition(const sf::Vector2f const& newpos) {
	this->position = newpos;
}
sf::Sprite& Entita::GetSprite() {
	return sprite;
}
void Entita::SetSprite(sf::Sprite sprite) {
	this->sprite = sprite;
}
sf::FloatRect Entita::GetCollRect() {
	return rectColl;
}
void Entita::setContext(SharedContext& context) {
	this->context = context;
}
unsigned int Entita::GetId() {
	return id;
}
void Entita::setId(unsigned int id1) {
	id = id1;
}

void Entita::SetEntityType(const std::string& newType)
{
	entitytype = newType;
}

std::string Entita::GetEntityType()
{
	return entitytype;
}



bool Entita::Touchable(float n1) {
	float x = abs(n1);

	if (x < 0.84)
		return true;

	return false;
}

void Entita::PreparaAttacco(int isSkill) {
	// attivo l'attacco e setto quale skill è
	SkillAttack = isSkill;
	Attacking = true;
}
void Entita::PreparaInterazione() {
	// setto l'interazione a true
	Interacting = true;
}

bool Entita::isBlockedW()
{
	return isblockedW;
}

bool Entita::isBlockedS()
{
	return isblockedS;
}

bool Entita::isBlockedA()
{
	return isblockedA;
}

bool Entita::isBlockedD()
{
	return isblockedD;
}

void Entita::RegenHitPoints() {
	sf::Time regenHP= clockVitalita.getElapsedTime();
	if (regenHP.asSeconds() >= speedHitPointsRecovery) {
		regenHP = clockVitalita.restart();
		vitalita += 1;
	}
}
void Entita::setMap(const std::string& map) {
	this->map = map;
}
std::string Entita::getMap() {
	return this->map;
}
void Entita::DrawEquipment() {
	inventario.DrawItems();
}