#include "Nemico.h"
#include "Mondo.h"

void Nemico::Movimento(const float &x, const float &y) {
	oldPosition = position;
	position += sf::Vector2f(x, y);
	A = false, D = false, S = false, W = false;
	if (x > 0) 
		D = true;
	else if (x < 0)
		A = true;
		

	if (y > 0) 
		S = true;
	else if (y < 0) 
		W = true;
		
	
		

	sprite.move(x, y);

	updateCollRect(); //aggiorna le informazioni sulle collisioni
}
bool Nemico::Attacco(Entita*ent, int isSkill) {
	return 0;
}
void Nemico::PreparaMovimento() {
	sf::Time elapsed = clockDecisioneMovimento.getElapsedTime();
	if (elapsed.asSeconds() > 2.0f) {
		int value = rand() % 4;

		switch (value)
		{
		case 0:
			Movimento(GetVelocita(), 0);
			animpg.SwitchAnimation("animationD");
			break;
		case 1:
			Movimento(-GetVelocita(), 0);
			animpg.SwitchAnimation("animationA");
			break;
		case 2:
			Movimento(0, GetVelocita());
			animpg.SwitchAnimation("animationS");
			break;
		case 3:
			Movimento(0, -GetVelocita());
			animpg.SwitchAnimation("animationW");
			break;
		default:
			break;
		}
		
		clockDecisioneMovimento.restart();
	}
	if (this->D && !isblockedD) {
		Movimento(GetVelocita(), 0);
	}
	else if (this->A && !isblockedA) {
		Movimento(-GetVelocita(), 0);
	}
	else if (this->W && !isblockedW) {
		Movimento(0, -GetVelocita());
	}
	else if (this->S && !isblockedS) {
		Movimento(0, GetVelocita());
	}

}

sf::Clock Nemico::getClock()
{
	return clockDecisioneMovimento;
}
