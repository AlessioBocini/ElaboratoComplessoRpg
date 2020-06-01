#pragma once
#include "Equipaggiamento.h"

class Armatura : public Equipaggiamento {
private:
	int vitalita;
public:
	int GetVitalita() {
		return this->vitalita;
	}
	void SetVitalita(int const& vit) {
		this->vitalita = vit;
	}
	Armatura(std::string nome, int vitalita) : vitalita(vitalita), Equipaggiamento(nome){}
};