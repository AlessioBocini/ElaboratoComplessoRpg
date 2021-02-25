#pragma once

#include "Entita.h"

template <class AStrategy>
class Context {
public:
	unsigned short int  Operation() {
		return theStrategy.GetInfo();
	}
	void Prepare(Entita* ent1, Entita* ent2) {
		theStrategy.Algorithm(ent1, ent2);
	}
private:
	AStrategy theStrategy;
};

class MyStrategy {
private:
	
public:
	virtual unsigned short int GetInfo() = 0;
	void Algorithm(Entita* ent1, Entita* ent2){}
	virtual ~MyStrategy(){}
};



