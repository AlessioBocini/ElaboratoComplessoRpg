#pragma once
#include "Equipaggiamento.h"
class Arma : public Equipaggiamento {
private:
	int forza;
public:
	int GetForza() {
		return this->forza;
	}
	void SetForza(int const& forza) {
		this->forza = forza;
	}
	Arma(std::string nome, int forza) : Equipaggiamento(nome), forza(forza) {}
};