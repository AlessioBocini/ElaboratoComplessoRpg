#pragma once
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "SharedContext.h"
#include "Collisione.h"

class Entita {
public:
	bool isblockedW;
	bool isblockedS;
	bool isblockedA;
	bool isblockedD;
	virtual void Movimento(int x , int y) = 0;
	virtual void Attacco(bool isSkill) = 0;
	std::string GetNome() {
		return this->nome;
	}
	void SetNome(std::string newnome) {
		this->nome = newnome;
	}
	int GetVitalita() {
		return this->vitalita;
	}
	void SetVitalita(int vit) {
		this->vitalita = vit;
	}
	float  GetVelocita() {
		return this->velocita;
	}
	void SetVelocita(float vel) {
		this->velocita = vel;
	}
	int GetForza() {
		return this->forza;
	}
	void SetForza(int const& forza) {
		this->forza = forza;
	}
	int GetLivello() {
		return this->livello;
	}
	void SetLivello(int const& liv) {
		this->livello = liv;
	}
	sf::Vector2f GetPosition() {
		return this->position;
	}
	void SetPosition(sf::Vector2f const& newpos) {
		this->position = newpos;
	}
	sf::Sprite& GetSprite() {
		return this->sprite;
	}
	void SetSprite(sf::Sprite sprite) {
		this->sprite = sprite;
	}
	sf::FloatRect GetCollRect() {
		return rectColl;
	}
	void setContext(SharedContext* context) {
		this->context = context;
	}
	void CheckCollisions(SharedContext* context);
	void ResolveCollisions(SharedContext* context);
	


	Entita(std::string nome, int forza, int vitalita, int livello, float velocita, sf::Vector2f pos, SharedContext *context) : context(context),vitalita(vitalita), nome(nome), forza(forza), velocita(velocita), livello(livello), sprite(sf::Sprite()) , isblockedA(false), isblockedD(false), isblockedS(false), isblockedW(false) {
		SetSizeRC(20, 26);
	}
	virtual ~Entita() {}
protected:
	void SetSizeRC(const float& x, const float& y) {
		sizeRC = sf::Vector2f(x, y);
		updateCollRect();
	}
	void updateCollRect() {
		rectColl = sf::FloatRect(position.x, position.y , sizeRC.x, sizeRC.y);
	}
	
	std::string nome;
	int vitalita;
	float velocita;
	std::string entitytype;
	int forza;
	int livello;
	sf::Vector2f position;
	sf::Vector2f oldPosition;
	sf::FloatRect rectColl;
	sf::Vector2f sizeRC;//size del Rect di Collisione 
	Collisions colls;
	sf::Sprite sprite;
	SharedContext* context;
};