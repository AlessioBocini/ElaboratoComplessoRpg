#pragma once
#include "Entita.h"
#include <string>
#include "Inventario.h"
#include "Skill.h"
#include "Arma.h"
#include "Armatura.h"
#include <iostream>
#include "Quickslot.h"
#include "Subject.h"

class Giocatore : public Entita {
private:
	
	std::vector<Quickslot> quickslots; 
	int stamina;
	int maxstamina;

	float speedStaminaRecovery = 2.0f;
	float staminaSpeedRunning = 0.5f;

	bool running;

	sf::Clock clockStamina;
	sf::Clock clockRunningStamina;
	Subject subject;
	float exp;
	float expToLvlUp = 500;
	unsigned int mobskilled;
	void LevelUp();
public:
	bool Attacco(Entita*ent, int isSkill) override;
	void Movimento(const float &x, const float &y) override;

	bool EquipWeapon(const Arma const& obj);
	bool EquipArmor(const Armatura const& obj);
	bool Interazione(Entita & ent) override;
	int GetStamina() const; 
	void SetStamina(int stam);
	int GetMaxStamina() const;
	void SetMaxStamina(int stam);
	float GetExp() const;
	void SetExp(float newexp);
	void ToggleInventory();
	void RegenStamina();
	void StaminaConsRunning();
	std::vector<Quickslot>* GetQuickslots();
	bool isRunning() const;
	void SetRunning(bool run);
	Subject& GetSubject();
	void IncreaseMobsKilled(unsigned int value = 1);
	unsigned int GetMobsKilled();

	void ProvideLoot(unsigned int money, unsigned int exp, std::vector<Equipaggiamento> equip = {});
	Giocatore(std::string const& nome, int forza, int  vitalita, int stamina, int livello, float velocita, const sf::Vector2f &pos, float exp, unsigned int id, SharedContext& context, const std::string const &entitytype) :Entita(nome, forza, vitalita, livello, velocita, pos, id, context, entitytype),stamina(stamina),maxstamina(stamina) ,exp(exp) ,quickslots(std::vector<Quickslot>()), mobskilled(0){}
	//Giocatore(std::string const& nome, const sf::Vector2f &pos) : Giocatore(nome, 100, 100, 100, 1, 100, pos, 0, 1, nullptr, "Player") {}
	Giocatore(std::string const& nome, const sf::Vector2f& pos,  SharedContext& context) : Giocatore(nome, 1, 100, 100, 1, 100, pos, 0, 0, context, "Player") {}
	~Giocatore() override{}
}; 