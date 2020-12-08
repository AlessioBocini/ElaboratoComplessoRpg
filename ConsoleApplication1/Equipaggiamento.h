#pragma once
#include <string>

class Equipaggiamento {
protected:
	std::string nome;
public:
	std::string GetNomeEquip() {
		return this->nome;
	}
	void SetNomeEquip(std::string nome) {
		this->nome = nome;
	}

	Equipaggiamento(std::string nome) : nome(nome) {}
};