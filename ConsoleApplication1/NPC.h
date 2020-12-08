#pragma once
#include "Entita.h"

class Npc : public Entita {
public:
	Npc(std::string nome, int forza, int vitalita, int livello, float velocita, sf::Vector2f pos, unsigned int id, SharedContext* context, std::string entityType) : Entita(nome, forza, vitalita, livello, velocita, pos, id, context, entityType) {}
	~Npc() {}

	int getTypeOfNpc();
	void Attacco(bool isSkill) override;
	void Movimento(float x, float y) override;
	void setTypeOfNpc(const int &type);
	std::string getMap();
	void setMap(const std::string& map);

private:
	int typeofNpc;
	std::string map;
};