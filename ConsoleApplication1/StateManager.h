#pragma once
#include <vector>
#include <vector>
#include <unordered_map>
#include "Intro_State.h"
#include "MainMenu_State.h"
#include "Game_State.h"
#include "Paused_State.h"
#include "SharedContext.h"

class GameManager; // forward declaration del GameManager.

// tipi di stato
enum class StateType {
	Intro = 1, MainMenu, Game, Paused, GameOver
};


using StateContainer = std::vector<std::pair<StateType, BaseState*>>;	// contenitore per collegare uno tipo di stato con un BaseState.

using TypeContainer = std::vector<StateType>;	//vettore contenente gli StateType.

using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>; //è un contenitore associativo per collegare assieme a ciascuna StateType
																					 // la funzione che genera tale stato.


class StateManager {
public:

	StateManager(SharedContext& shared, GameManager* gm);
	~StateManager();

	void Update(const sf::Time& time);
	void Draw();

	void ProcessRequests();

	SharedContext* GetContext();
	bool HasState(const StateType& type);

	void SwitchTo(const StateType& type);
	void Remove(const StateType& type);

private:
	void CreateState(const StateType& type);
	void RemoveState(const StateType& type);

	// è una funzione che si occupa di mappare uno stato ad una funzione che restituisce il puntatore della memoria appena allocata.
	template<class T>
	void RegisterState(const StateType& l_type) {
		stateFactory[l_type] = [this]() -> BaseState*
		{
			return new T(this);
		};
	}
	SharedContext& shared;
	StateContainer states;
	StateFactory stateFactory;
	TypeContainer toRemove;
};

