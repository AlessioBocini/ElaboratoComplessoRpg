#pragma once
#include "Entita.h"
#include <string>
#include "Inventario.h"
#include "Skill.h"
#include "Arma.h"
#include "Armatura.h"


class Giocatore : public Entita {
private:
	Inventario inventario;
	std::vector<Skill> skills;
	int stamina;
	float exp;
public:
	void Attacco(bool isSkill) override;

	void Movimento(int x , int y) override; 
	bool EquipWeapon(Arma const& obj);
	bool EquipArmor(Armatura const& obj);
	bool Interazione(Entita const& ent);
	int GetStamina() {
		return this->stamina;
	}
	void SetStamina(int stam) {
		this->stamina = stam;
	}
	float GetExp() {
		return this->exp;
	}
	void SetExp(float newexp) {
		this->exp = newexp;

	}
	Giocatore(std::string const& nome, int forza, int  vitalita, int stamina, int livello, float velocita, sf::Vector2f pos, float exp) :Entita(nome, forza, vitalita, livello, velocita, pos) {
		this->SetStamina(stamina);
		inventario = Inventario();
		skills = std::vector<Skill>();
		this->SetExp(exp);
	}
	Giocatore(std::string const& nome, sf::Vector2f pos) : Giocatore(nome, 100, 100, 100, 1, 1, pos, 0) {}
};
