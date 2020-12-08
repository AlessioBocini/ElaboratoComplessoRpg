#pragma once

#include "Nemico.h"
class Miniboss : public Nemico {
private:
	std::string titolo;
public:
	std::string GetTitolo() {
		return this->titolo;
	}
	bool setTitolo(std::string const& titolo) {
		this->titolo = titolo;
	}
};