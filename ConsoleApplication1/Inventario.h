#pragma once
#include <vector>
#include "Equipaggiamento.h"

class Inventario {
private:
	int numeroSlot;
	std::vector<Equipaggiamento> equip;
public:
	bool EliminaOggetto(Equipaggiamento const& obj);
	bool AggiungiOggetto(Equipaggiamento const& obj);
};