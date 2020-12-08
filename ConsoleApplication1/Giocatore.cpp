#include "Giocatore.h"
#include <iostream>
#include "Tile.h"

#include "Mondo.h"


void Giocatore::Attacco(bool isSkill) {
}


void Giocatore::Movimento(float x, float y) {
	oldPosition = position;
	position += sf::Vector2f(x, y);
	A = false, D = false, S = false, W = false;
	if (x > 0) 
		D = true;
	else if(x<0)
		A = true;

	if (y > 0)
		S = true;
	else if(y<0)
		W = true;

	sprite.move(x, y);
	updateCollRect(); //aggiorna le informazioni sulle collisioni
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

