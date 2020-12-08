#pragma once
#include "Entita.h"
#include "Giocatore.h"
class Nemico : public Entita {
public:
	Nemico(std::string nome, int forza, int vitalita, int livello, float velocita, sf::Vector2f pos, unsigned int id, SharedContext* context, std::string entityType) : Entita(nome, forza, vitalita, livello, velocita, pos, id, context, entityType) {}
	~Nemico() {}
	void Attacco(bool isSkill) override;
	void Movimento(float x, float y) override;
};
