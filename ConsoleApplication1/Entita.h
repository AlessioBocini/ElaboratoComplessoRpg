#pragma once
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "SharedContext.h"
#include "Collisione.h"
#include "Animator.h"
#include "Inventario.h"
enum class EntityType { Enemy, MiniBoss, Player, NPC };
enum class NpcType { Guard, Shopkeeper };
enum class EnemyType { Skeleton, Crystal, Bandit};
enum class EntityState { Idle, Walking, Attacking, Dying };
using AnimSet = Animator::Animation;
class Entita {
public:
	virtual void Movimento(const float &x, const float &y) = 0;
	virtual bool Attacco(Entita* ent, int isSkill) = 0;
	void PreparaAttacco(int isSkill);
	void PreparaInterazione();
	
	bool isBlockedW();
	bool isBlockedS();
	bool isBlockedA();
	bool isBlockedD();

	void Update(sf::Time const& dt);
	std::string GetNome();
	void SetNome(std::string newnome);
	int GetVitalita();
	void SetVitalita(int vit);
	int GetMaxVitalita();
	void SetMaxVitalita(int vit);
	float  GetVelocita();
	void SetVelocita(float vel);
	int GetForza();
	void SetForza(int const& forza);
	int GetLivello();
	void SetLivello(int const& liv);
	Animator* GetAnimpg();
	std::vector<AnimSet> GetAnimations();
	Inventario* GetInventario();
	void SetLastDirection(char newDirection);
	char GetLastDirection();
	sf::Vector2f GetPosition();
	void SetPosition(const sf::Vector2f const& newpos);
	sf::Sprite& GetSprite();
	void SetSprite(sf::Sprite sprite);
	sf::FloatRect GetCollRect();
	void setContext(SharedContext& context);
	unsigned int GetId();
	void setId(unsigned int id1);
	void SetEntityType(const std::string& newType);
	std::string GetEntityType();
	void setSpawnPoint(sf::Vector2f pos);
	void setMap(const std::string& map);
	std::string getMap();

	void CheckCollisions(/*SharedContext& context*/);
	// è una funzione che mi serve a determinare se ci sono state collissioni e di che tipo
	void CollisionEntity(Entita* ent/*, SharedContext* context*/);
	void ResolveCollisions(/*SharedContext* context*/); // è una funzione che mi server per determinare cosa fare per le determinate collissioni, che decisioni prendere.
	void ResolveCollisionEntity(/*SharedContext* context*/);
	Entita(const std::string &nome, const int &forza, const int &vitalita, const int &livello, const float &velocita, const sf::Vector2f &pos, unsigned int id, SharedContext& context, const std::string const &entityType) : entitytype(entityType), id(id), context(context), vitalita(vitalita),maxvitalita(vitalita), nome(nome), forza(forza), velocita(velocita), livello(livello), sprite(sf::Sprite()), isblockedA(false), isblockedD(false), isblockedS(false), isblockedW(false), A(false),D(false),W(false),S(false),Attacking(false),Interacting(false), lastDirection('S'),animpg(sprite),sizeRC(sf::Vector2f(20,26)), inventario(context) {
		
		updateCollRect();
	}
	virtual ~Entita() {}
private:
	std::vector<Entita*> entitiescollided;

	void SetSizeRC(const float& x, const float& y) {
		//funzione per settare la nuova area di collisione attorno all'entità
		sizeRC = sf::Vector2f(x, y);
		updateCollRect();
	}	
	sf::FloatRect rectColl;
	sf::Vector2f sizeRC; //size del Rect di Collisione dell'entità
	Collisions colls;
protected:
	void updateCollRect() {
		// è necessario aggiornare il rectColl, a causa del fatto che l'entità si muove.
		// in altre parole cambierà position.x e position.y
		rectColl = sf::FloatRect(position.x, position.y, sizeRC.x, sizeRC.y);
	}
	sf::Vector2f position;
	sf::Vector2f oldPosition;
	sf::Sprite sprite;
	std::vector<AnimSet> animations;
	Animator animpg;
	
	Inventario inventario;
	
	bool isblockedW;
	bool isblockedS;
	bool isblockedA;
	bool isblockedD;
	
	bool Touchable(float n1);
	void DrawEquipment();
	void RegenHitPoints();

	// Controlli
	bool W;
	bool S;
	bool A;
	bool D;
	char lastDirection;
	bool Attacking;
	int SkillAttack;
	bool Interacting;

	sf::Clock clockAttack;
	sf::Clock clockVitalita;
	float speedHitPointsRecovery = 2.5f;
	float cooldownAutoAttack = 0.5f;
	
	std::string nome;
	int vitalita;
	int maxvitalita;
	float velocita;
	std::string entitytype;
	int forza;
	int livello;
	unsigned int id;
	std::string map;
	SharedContext& context;
};