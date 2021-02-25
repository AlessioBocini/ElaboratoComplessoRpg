#pragma once
#include "Strategy.h"
#include "Nemico.h"

class MovementStrategy : public MyStrategy{
public:
	unsigned short int GetInfo() override {
		return movimento;
	}

	void Algorithm(Entita* ent1, Entita* ent2);
	void Algorithm(Nemico* nem, Giocatore* player);
	~MovementStrategy() override {}
private:
	unsigned short int movimento;

};


