#include "Game.h"

//entita
void Entita::Attacco() {

}
void Entita::Movimento() {

}
// giocatore
void Giocatore::Attacco(std::string const& buttonPressed , bool isSkill){
}
bool Giocatore::Movimento(char const& buttonPressed) {
	bool isMovement = true;
	switch (buttonPressed)
	{
	case 'w': {
		
		GetSprite().move(0, -1*GetVelocita());
		break;
	}
	case 's': {
		GetSprite().move(0,GetVelocita());
		break;
	}
	case 'd': {
		GetSprite().move(GetVelocita(), 0);
		break;
	}
	case 'a': {
		GetSprite().move(-1 * (GetVelocita()),0);
		
		break;
	}
	default:
		isMovement = false;
		break;
	}

	return isMovement;
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
// equipaggiamento

bool Inventario::EliminaOggetto(Equipaggiamento const& equip) {
	return true;
}
bool Inventario::AggiungiOggetto(Equipaggiamento const& equip) {
	return true;
}

// Mondo
bool Territorio::ShowMap() {
	return true;
}


// GameManager

bool GameManager::CheckForLevelUp() {

	return true;
}
bool GameManager::isButtonPressedSKill(std::string const& buttonPressed) {
	return true;
}
bool GameManager::isGameOver() {
	return false;
}
bool GameManager::LoadGame() {
	return true;
}
bool GameManager::SaveGame() {
	return true;
}
void  GameManager::RegenStamina() {

}
bool GameManager::AggiungiSkill(Skill skill) {
	return true;
}