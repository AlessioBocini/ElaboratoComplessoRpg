#pragma once
#include "Entita.h"

class Npc : public Entita {
public:
	Npc(std::string nome, int forza, int vitalita, int livello, float velocita, sf::Vector2f pos, unsigned int id, SharedContext& context, std::string entityType) : Entita(nome, forza, vitalita, livello, velocita, pos, id, context, entityType),typeofNpc(-1) {}
	Npc(std::string nome, int forza, int vitalita, int livello, float velocita, sf::Vector2f pos, unsigned int id, SharedContext& context) : Npc(nome, forza, vitalita, livello, velocita, pos, id, context, ""){}
	~Npc() override {}

	int getTypeOfNpc() const;
	bool Attacco(Entita*ent,int isSkill) override;
	void Movimento(const float &x, const float &y) override;
	void setTypeOfNpc(const int &type);
	bool Interazione(Entita& ent) override;

private:
	int typeofNpc;
};