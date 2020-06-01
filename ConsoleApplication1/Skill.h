#pragma once

class Skill {
private:
	int costo;
	int moltiplicatoreDanno;
public:
	int GetCosto() {
		return this->costo;
	}
	int GetMoltiplicatoreDanno() {
		return this->moltiplicatoreDanno;
	}

	Skill(int costo, int moltiplicatoreDanno) : costo(costo), moltiplicatoreDanno(moltiplicatoreDanno) {}
};