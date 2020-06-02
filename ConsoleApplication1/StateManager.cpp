#include "StateManager.h"
#include <iostream>



StateManager::StateManager(SharedContext* shared, GameManager*gm) : shared(shared) , gamemanager(gm) {
	RegisterState<State_Intro>(StateType::Intro);
	RegisterState<State_MainMenu>(StateType::MainMenu);
	RegisterState<State_Game>(StateType::Game);
	RegisterState<State_Paused>(StateType::Paused);
}


StateManager::~StateManager() {
	for (auto& it : states) {
		it.second->OnDestroy();
		delete it.second;
	}
}

void StateManager::Draw() {
	if (states.empty()) return;
	if (states.back().second->IsTrasparent() && states.size() > 1) {
		auto it = states.end();
		while (it != states.begin()) {
			if (it != states.end()) {
				if (!it->second->IsTrasparent()) {
					break;
				}
			}
			--it;
		}
		for (; it != states.end(); ++it) {
			it->second->Draw();
		}
	}
	else {
		states.back().second->Draw();
	}
}


void StateManager::Update(const sf::Time& time) {
	if (states.empty()) return;
	if (states.back().second->IsTranscendent() && states.size() > 1) {
		auto it = states.end();
		while (it != states.begin()) {
			if (it != states.end()) {
				if (!it->second->IsTranscendent()) {
					break;
				}
			}
			--it;
		}
		for (; it != states.end(); ++it) {
			it->second->Update(time);
		}
	}
	else {
		states.back().second->Update(time);
	}
}

SharedContext* StateManager::GetContext() {
	return shared;
}
GameManager* StateManager::GetGameManager() {
	return gamemanager;
}

bool StateManager::HasState(const StateType& type) {
	for (auto it = states.begin(); it != states.end(); it++) {
		if (it->first == type) {
			auto removed = std::find(toRemove.begin(), toRemove.end(), type);
			if (removed == toRemove.end())
				return  true;

			return false;
		}
	}
	return false;
}
void StateManager::Remove(const StateType& type) {
	toRemove.push_back(type);
}
void StateManager::ProcessRequests() {
	while (toRemove.begin() != toRemove.end()) {
		RemoveState(*toRemove.begin());
		toRemove.erase(toRemove.begin());
	}
}

void StateManager::SwitchTo(const StateType& type) {
	shared->eventManager->SetCurrentState(type);
	for (auto it = states.begin(); it != states.end(); it++) {
		if (it->first == type) {
			states.back().second->Deactivate();
			StateType tmp_type = it->first;
			BaseState* tmp_state = it->second;
			states.erase(it);
			states.emplace_back(tmp_type, tmp_state);
			tmp_state->Activate();
			return;
		}
	}
	if (!states.empty()) {
		states.back().second->Deactivate();
	}
	CreateState(type);
	states.back().second->Activate();

}

void StateManager::CreateState(const StateType& type) {
	auto newState = stateFactory.find(type);
	if (newState == stateFactory.end()) return;
	BaseState* state = newState->second();
	states.emplace_back(type, state);
	state->OnCreate();
}

void StateManager::RemoveState(const StateType& type) {
	for (auto it = states.begin(); it != states.end(); it++) {
		if (it->first == type) {
			it->second->OnDestroy();	//dealloco la memoria
			delete it->second;
			states.erase(it);
			return;
		}
	}
}




