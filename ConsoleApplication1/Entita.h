#pragma once
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "SharedContext.h"
#include "Collisione.h"
#include "Animator.h"
enum class EntityType { Enemy, MiniBoss, Player};
enum class EntityState {Idle, Walking, Attacking, Dying};
using AnimSet = Animator::Animation;
class Entita {
public:
	virtual void Movimento(float x , float y) = 0;
	virtual void Attacco(bool isSkill) = 0;

	bool isblockedW;
	bool isblockedS;
	bool isblockedA;
	bool isblockedD;
	std::vector<AnimSet> animations;
	Animator animpg;

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
	unsigned int GetId() {
		return id;
	}
	void setId(unsigned int id1) {
		id = id1;
	}
	void setSpawnPoint(sf::Vector2f pos);

	void CheckCollisions(SharedContext* context);
	// è una funzione che mi serve a determinare se ci sono state collissioni e di che tipo
	void ResolveCollisions(SharedContext* context); // è una funzione che mi server per determinare cosa fare per le determinate collissioni, che decisioni prendere.

	Entita(std::string nome, int forza, int vitalita, int livello, float velocita, sf::Vector2f pos, unsigned int id, SharedContext* context,std::string entityType) : entitytype(entityType), id(id), context(context), vitalita(vitalita), nome(nome), forza(forza), velocita(velocita), livello(livello), sprite(sf::Sprite()), isblockedA(false), isblockedD(false), isblockedS(false), isblockedW(false), animpg(sprite) {
		SetSizeRC(20, 26);
		setSpawnPoint(pos);
	}
	virtual ~Entita() {}
protected:
	
	void SetSizeRC(const float& x, const float& y) {
		//funzione per settare la nuova area di collisione attorno all'entità
		sizeRC = sf::Vector2f(x, y);
		updateCollRect();
	}
	void updateCollRect() {
		// è necessario aggiornare il rectColl, a causa del fatto che l'entità si muove.
		// in altre parole cambierà position.x e position.y
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
	sf::Vector2f sizeRC; //size del Rect di Collisione dell'entità
	Collisions colls;
	sf::Sprite sprite;
	unsigned int id;
	SharedContext* context;
};