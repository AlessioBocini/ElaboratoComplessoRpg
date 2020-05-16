
#ifndef Game_Manager
	#define Game_Manager

#include <string>
#include <vector>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics.hpp>
/*
*******************************************
*********** Equipaggiamento ***************
*******************************************
*/

class Equipaggiamento {
private:
	std::string nome;
public:
	std::string GetNomeEquip() {
		return this->nome;
	}
	void SetNomeEquip(std::string nome) {
		this->nome = nome;
	}
};

class Armatura : public Equipaggiamento {
private:
	int vitalita;
public:
	int GetVitalita() {
		return this->vitalita;
	}
	void SetVitalita(int const& vit) {
		this->vitalita = vit;
	}
	Armatura(std::string nome, int vitalita) {
		this->SetVitalita(vitalita);
		this->SetNomeEquip(nome);
	}
};
class Arma : public Equipaggiamento {
private:
	int forza;
public:
	int GetForza() {
		return this->forza;
	}
	void SetForza(int const& forza) {
		this->forza = forza;
	}
	Arma(std::string nome, int forza) {
		this->SetForza(forza);
		this->SetNomeEquip(nome);
	}
};


class Inventario {
private:
	int numeroSlot;
	std::vector<Equipaggiamento> equip;
public:
	bool EliminaOggetto(Equipaggiamento const& obj);
	bool AggiungiOggetto(Equipaggiamento const& obj);
};


/*
**************************************
************ Skills ******************
**************************************
*/
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
};

/*
*********************************
****** Manager ******************
*********************************
*/
class GameManager {

public:
	bool isButtonPressedSKill(std::string const& buttonPressed);
	bool AggiungiSkill(Skill skill);
	bool isGameOver();
	bool LoadGame();
	bool SaveGame();
	bool CheckForLevelUp();
	void RegenStamina();
};

/*
*************************************************
***************   ENTITA    *********************
*************************************************
*/

/*
	Entità.
*/

class EntitaAbstract{
public:
	virtual void Movimento()  = 0;
	virtual void Attacco()   = 0;
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
	EntitaAbstract(std::string nome, int forza, int vitalita, int livello, float velocita, sf::Vector2f pos) {
		this->SetVitalita(vitalita);
		this->SetForza(forza);
		this->SetLivello(livello);
		this->SetVelocita(velocita);
		this->SetNome(nome);
		this->SetSprite(sf::Sprite());
		this->SetPosition(pos);
	}
private:
	std::string nome;
	int vitalita;
	float velocita;
	int forza;
	int livello;
	sf::Vector2f position;
	sf::Sprite sprite;
};

class Entita : public EntitaAbstract{
public:
	void Movimento() override;
	void Attacco() override;
	Entita(std::string nome, sf::Vector2f pos) :Entita(nome, 100, 100, 1, 0.7, pos) {}
	Entita(std::string nome, int forza, int vitalita, int livello, float velocita, sf::Vector2f pos) : EntitaAbstract( nome,  forza, vitalita,livello,velocita, pos){}
};

/*
Nemico
*/
class Nemico : public Entita {

};
/*
NPC
*/
class Npc : public Entita{

};
/*
Miniboss
*/
class Miniboss : public Nemico{
private:
	std::string titolo;
public:
	std::string GetTitolo() {
		return this->titolo;
	}
	bool setTitolo(std::string const& titolo){
		this->titolo = titolo;
	}
};
/*
NemicoComune
*/
class NemicoComune : public Nemico {

};

/*
Giocatore
*/
class Giocatore : public Entita{
private:
	Inventario inventario;
	std::vector<Skill> skills;
	int stamina;
	float exp;
public:
	void Attacco(std::string const& buttonPressed, bool isSkill);
	bool Movimento(char const& buttonPressed);
	bool EquipWeapon(Arma const& obj);
	bool EquipArmor(Armatura const& obj);
	bool Interazione(Entita const& ent);
	int GetStamina() {
		return this->stamina;
	}
	void SetStamina(int stam) {
		this->stamina = stam;
	}
	float GetExp() {
		return this->exp;
	}
	void SetExp(float newexp) {
		this->exp = newexp;

	}
	Giocatore(std::string const& nome, int forza, int  vitalita, int stamina, int livello, float velocita, sf::Vector2f pos, float exp) :Entita(nome,forza,vitalita,livello,velocita,pos){
		this->SetStamina(stamina);
		inventario = Inventario();
		skills = std::vector<Skill>();
		this->SetExp(exp);
	}
	Giocatore(std::string const& nome, sf::Vector2f pos) : Giocatore(nome, 100, 100, 100, 1, 0.05, pos,0) {}
};

/*
******************************
*********** Mondo ************
******************************
*/
class Territorio {
	
public:
	bool ShowMap();
};

class Mondo {
private:
	GameManager manager;
	sf::Vector2i size;
	int nTerritori;
	std::vector<Territorio> territori;
public:
	sf::Vector2i GetSize() {
		return this->size;
	}
	int GetNTerritori() {
		return this->nTerritori;
	}
};


#endif

