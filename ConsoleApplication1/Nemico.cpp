#include "Nemico.h"


void Nemico::Movimento(float x, float y) {
	oldPosition = position;
	position += sf::Vector2f(x, y);
	sprite.move(x, y);

	updateCollRect(); //aggiorna le informazioni sulle collisioni
}
void Nemico::Attacco(bool isSkill) {

}


