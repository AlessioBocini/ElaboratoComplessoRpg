#include "Giocatore.h"
#include <iostream>
#include "Tile.h"

#include "Mondo.h"

void Giocatore::Attacco( bool isSkill) {
}


void Giocatore::Movimento(int x , int y) {

	

	oldPosition = position;	
	position += sf::Vector2f(x, y);
	GetSprite().move(x, y);

	updateCollRect();
}

bool Giocatore::EquipArmor(Armatura const& obj) {
	return true;
}
bool Giocatore::EquipWeapon(Arma const& obj) {
	return true;
}
bool Giocatore::Interazione(Entita const& ent) {
	return true;
}
