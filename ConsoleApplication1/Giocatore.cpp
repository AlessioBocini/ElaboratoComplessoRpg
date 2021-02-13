#include "Giocatore.h"
#include <iostream>
#include "Tile.h"

#include "Mondo.h"
#include "Nemico.h"


void Giocatore::LevelUp()
{
	this->livello++;
	this->exp = 0;
	this->vitalita = this->maxvitalita;
	this->stamina = this->maxstamina;
	//this->expToLvlUp++; lascio fisso a 500
	// TODO faccio fare la scelta tra 3  oggetti/skill/statistiche 
}

bool Giocatore::Attacco(Entita *ent, int Skill) {
	bool executed = false;
	if (!ent->isAlive()) 
		return executed;

	ent->PreparaAttacco(); //il nemico si arrabbia
	Nemico* nem = dynamic_cast<Nemico*>(ent);
	if (nem != nullptr) {
		if (!nem->isFollowing()) {
			nem->PreparaInseguimento();
		}
	}

	switch (Skill)
	{
	case -1: {
		if ((stamina - 10) >= 0) {
			stamina -= 10;

			bool usingweap = false;
			if (GetInventario()->GetWeapon() != nullptr)
				usingweap = GetInventario()->GetWeapon()->GetUsing();

			int weapDmg = (usingweap == true) ? GetInventario()->GetWeapon()->GetForza() : 0;

			ent->Hit(forza*(10 + weapDmg));
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

int Giocatore::GetStamina() const
{
	return stamina;
}

void Giocatore::SetStamina(int stam)
{
	this->stamina = stam;
}

int Giocatore::GetMaxStamina() const
{
	return maxstamina;
}

void Giocatore::SetMaxStamina(int stam)
{
	this->maxstamina = stam;
}

float Giocatore::GetExp() const
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
	if (!running) {
		sf::Time regenStamina = clockStamina.getElapsedTime();
		if (regenStamina.asSeconds() >= speedStaminaRecovery) {
			clockStamina.restart();
			stamina += 1;
		}
	}
}

void Giocatore::StaminaConsRunning()
{
	if (running) {
		sf::Time consumeStamina = clockRunningStamina.getElapsedTime();
		if (consumeStamina.asSeconds() >= staminaSpeedRunning) {
			clockRunningStamina.restart();
			stamina -= 1;
		}
	}
}

std::vector<Quickslot>* Giocatore::GetQuickslots() 
{
	return &quickslots;
}

bool Giocatore::isRunning() const
{
	return running;
}
void Giocatore::SetRunning(bool run) {
	running = run;
}
void Giocatore::ProvideLoot(unsigned int money, unsigned int exp, std::vector<Equipaggiamento> equip)
{
	this->exp += exp;
	std::cout << "Hai ottenuto " << exp << " exp" << std::endl;
	if (this->exp >= this->expToLvlUp) {
		this->LevelUp();
		std::cout << "Congratulazioni, sei passato al livello "<<livello<< std::endl;
	}
	this->inventario.AddDenaro(money);

	for (auto it : equip)
		this->inventario.AggiungiOggetto(it,0);

}
