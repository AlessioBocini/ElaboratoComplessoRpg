#include "Giocatore.h"



void Giocatore::Attacco( bool isSkill) {
}


void Giocatore::Movimento(int x , int y) {
	GetSprite().move(x, y);
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