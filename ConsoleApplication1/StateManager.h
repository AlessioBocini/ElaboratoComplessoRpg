#pragma once
#include <vector>
#include "BaseState.h"
#include <unordered_map>
#include <functional>
enum class StateType {
	Intro = 1, MainMenu, Game, Paused, GameOver
};
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

using TypeContainer = std::vector<StateType>;

using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>;

//TODO : Leggi il capitolo del Event manager, SharedContext e continua lo state pattern.
class StateManager {
public :

	StateManager(SharedContext* shared);
	~StateManager();

	void Update(const sf::Time& time);
	void Draw();

	void ProcessRequests();

	sharedContext* GetContext();
	bool HasState(const StateType& type);

	void SwitchTo(const StateType& type);
	void Remove(const StateType& type);

private:
	void CreateState(const StateType& type);
	void RemoveState(const StateType& type);

	template<class T> void RegisterState(const StateType& type) {}

	SharedContext* shared;
	StateContainer states;
	StateFactory stateFactory;
	TypeContainer toRemove;
};
