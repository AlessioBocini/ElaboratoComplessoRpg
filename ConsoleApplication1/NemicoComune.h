#pragma once
#include "Nemico.h"
class NemicoComune : public Nemico {
public:
	NemicoComune(std::string nome, int forza, int vitalita, int livello, float velocita, sf::Vector2f pos, unsigned int id, SharedContext* context, std::string entityType) : Nemico(nome, forza, vitalita, livello, velocita, pos, id, context, entityType) {}
	~NemicoComune() {}


};