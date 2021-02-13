#pragma once
#include "Entita.h"
#include "Giocatore.h"
class Nemico : public Entita {
public:
	Nemico(const std::string &nome, const int &forza, const int &vitalita,const int &livello, const float &velocita, const sf::Vector2f &pos, unsigned int id, SharedContext& context, const std::string const& entityType) : Entita(nome, forza, vitalita, livello, velocita, pos, id, context, entityType),enemyType(-1) {}
	Nemico(const std::string &nome, const int &forza, const int &vitalita,const int &livello, const float &velocita, const sf::Vector2f &pos, unsigned int id, SharedContext& context) : Nemico(nome, forza, vitalita, livello, velocita, pos, id, context, ""){}
	~Nemico() override {}
	bool Attacco(Entita*ent,int isSkill) override;
	void Movimento(const float &x, const float &y) override;
	void PreparaMovimento();
	int GetEnemyType() const {
		return enemyType;
	}
	void SetEnemyType(const int &type) {
		enemyType = type;
	}
	sf::Clock getClock() const;
	// run to player
	int nextStep();
	void PreparaInseguimento();
	void StopInseguimento();
	bool isFollowing();


private:
	int enemyType;
	bool following;

	sf::Clock clockDecisioneMovimento;
	int decisioneMovimentoTime = 2;

	sf::Clock clockFaseInseguimento;
	int faseInseguimentoTime = 15;

	sf::Clock clockFaseAttacco;
};
