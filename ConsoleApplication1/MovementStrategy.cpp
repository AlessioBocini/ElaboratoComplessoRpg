#include "MovementStrategy.h"

void MovementStrategy::Algorithm(Entita* ent1, Entita* ent2)
{
	movimento = 4;
	Nemico* nem = dynamic_cast<Nemico*>(ent1);
	Giocatore* player = dynamic_cast<Giocatore*>(ent2);
	if (nem != nullptr && player != nullptr) {
		Algorithm(nem, player);
	}
}

void MovementStrategy::Algorithm(Nemico* nem, Giocatore* player)
{
	movimento= 4;
	if (!nem->isFollowing()) {
		movimento = rand() % 4;
	}
	else {
		auto position = nem->GetPosition();
		int Tile_Size = 32;
		float myX = floor(position.x / Tile_Size), myY = floor(position.y / Tile_Size);
		float playerX = floor(player->GetPosition().x / Tile_Size), playerY = floor(player->GetPosition().y / Tile_Size);

		if (playerY - myY < 0) {
			//verso l'alto
			movimento = 3;
		}
		else if (playerY - myY > 0) {
			//verso basso
			movimento = 2;
		}

		if (playerX - myX > 0) {
			//verso destra
			movimento = 0;
		}
		else if (playerX - myX < 0) {
			//verso sinistra
			movimento = 1;
		}
	}
}
