#include "Giocatore.h"
#include <iostream>
#include "Tile.h"

#include "Mondo.h"


bool Giocatore::Attacco(Entita *ent, int Skill) {
	bool executed = false;

	switch (Skill)
	{
	case -1: {
		if ((stamina - 10) >= 0) {
			stamina -= 10;
			ent->SetVitalita(ent->GetVitalita()-(forza/100));
			executed = true;
		}
		
		break;
	}
		
	default:
		break;
	}
	Attacking = false;
	return executed;
}


void Giocatore::Movimento(const float &x, const float &y) {
	oldPosition = position;
	position += sf::Vector2f(x, y);
	A = false, D = false, S = false, W = false;
	if (x > 0) {
		D = true;
		lastDirection = 'D';
	}
	else if (x < 0) {
		A = true;
		lastDirection = 'A';
	}
		

	if (y > 0) {
		S = true;
		lastDirection = 'S';
	}
	else if (y < 0) {
		W = true;
		lastDirection = 'W';
	}
		

	sprite.move(x, y);
	updateCollRect(); //aggiorna le informazioni sulle collisioni
}

bool Giocatore::EquipArmor(const Armatura const& obj) {
	return true;
}
bool Giocatore::EquipWeapon(const Arma const& obj) {
	return true;
}
bool Giocatore::Interazione(Entita & ent) {
	std::cout << "sto parlando con : " << ent.GetNome() << std::endl;
	Interacting = false;
	return true;
}

int Giocatore::GetStamina()
{
	return stamina;
}

void Giocatore::SetStamina(int stam)
{
	this->stamina = stam;
}

int Giocatore::GetMaxStamina()
{
	return maxstamina;
}

void Giocatore::SetMaxStamina(int stam)
{
	this->maxstamina = stam;
}

float Giocatore::GetExp()
{
	return exp;
}

void Giocatore::SetExp(float newexp)
{
	exp = newexp;
}

void Giocatore::ToggleInventory()
{
	inventario.ToggleVisibility();
}

void Giocatore::RegenStamina() {
		sf::Time regenStamina = clockStamina.getElapsedTime();
	if (regenStamina.asSeconds() >= speedStaminaRecovery) {
		regenStamina = clockStamina.restart();
		stamina += 1;
	}
}

std::vector<Quickslot>* Giocatore::GetQuickslots()
{
	return &quickslots;
}
