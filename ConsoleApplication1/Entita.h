#pragma once
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Sprite.hpp>


class Entita {
public:
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
	Entita(std::string nome, int forza, int vitalita, int livello, float velocita, sf::Vector2f pos) : vitalita(vitalita), nome(nome), forza(forza), velocita(velocita), livello(livello), sprite(sf::Sprite()), position(pos) {}
	virtual ~Entita() {}
protected:
	std::string nome;
	int vitalita;
	float velocita;
	int forza;
	int livello;
	sf::Vector2f position;
	sf::Sprite sprite;
};