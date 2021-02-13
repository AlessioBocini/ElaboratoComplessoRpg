#include "Nemico.h"
#include "Mondo.h"
#include "EntityManager.h"

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

int Nemico::nextStep()
{
	int value =4;
	if (!following) {
		value = rand() % 4;
		return value;
	}
	
	Giocatore* player = context.entityManager->GetGiocatore();
	float myX = floor(position.x/Tile_Size), myY = floor(position.y / Tile_Size), myOldX = oldPosition.x / Tile_Size, myOldY = oldPosition.y / Tile_Size;
	float playerX = floor(player->GetPosition().x / Tile_Size), playerY = floor(player->GetPosition().y / Tile_Size);


	if (playerY - myY < 0) {
		//verso il alto
		value = 3;
	}
	else if(playerY - myY > 0){
		//verso basso
		value = 2;
	}

	if (playerX - myX > 0) {
		//verso destra
		value = 0;
	}
	else if(playerX - myX < 0) {
		//verso sinistra
		value = 1;
	}
	
	return value;
}
void Nemico::PreparaInseguimento()
{
	clockFaseInseguimento.restart();
	following = true;
}
void Nemico::StopInseguimento()
{
	following = false;
}
bool Nemico::isFollowing()
{
	return following;
}
bool Nemico::Attacco(Entita*ent, int isSkill) {

	if (!isalive)return 1;

	Giocatore* player = dynamic_cast<Giocatore*>(ent); //only towards player
	if(player != nullptr)
		ent->Hit(forza * 10);
	
	return 0;
}
void Nemico::PreparaMovimento() {
	if (!isalive) return;
	sf::Time elapsed = clockDecisioneMovimento.getElapsedTime();
	int time = decisioneMovimentoTime;

	if (following) {
		if (clockFaseInseguimento.getElapsedTime().asSeconds() > faseInseguimentoTime) {
			following = false;
			Attacking = false;
		}
	}
	int speedreducer = 1;
	if (following) {
		time /= 3;
		speedreducer = 3;
	}
		

	if (elapsed.asSeconds() > time) {

		int value = nextStep();

		switch (value)
		{
		case 0:
			Movimento(GetVelocita()/speedreducer, 0);
			if (animpg.GetCurrentAnimationName() != "animationD")
				animpg.SwitchAnimation("animationD");
			break;
		case 1:
			Movimento(-GetVelocita() / speedreducer, 0);
			if (animpg.GetCurrentAnimationName() != "animationA")
				animpg.SwitchAnimation("animationA");
			break;
		case 2:
			Movimento(0, GetVelocita() / speedreducer);
			if (animpg.GetCurrentAnimationName() != "animationS")
				animpg.SwitchAnimation("animationS");
			break;
		case 3:
			Movimento(0, -GetVelocita() / speedreducer);
			if(animpg.GetCurrentAnimationName() != "animationW")
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

sf::Clock Nemico::getClock() const
{
	return clockDecisioneMovimento;
}
