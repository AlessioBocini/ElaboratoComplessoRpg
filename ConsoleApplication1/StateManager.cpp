#include "StateManager.h"
#include <iostream>



StateManager::StateManager(SharedContext* shared, GameManager*gm) : shared(shared) , gamemanager(gm) {
	RegisterState<State_Intro>(StateType::Intro); //lo stato State_Intro adesso ha una memoria allocata.
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

//simile all'update
void StateManager::Draw() {
	if (states.empty()) return;
	if (states.back().second->IsTrasparent() && states.size() > 1) {

		auto it = states.end();
		// uso un while per evitare l'errore nel caso in cui ci sia solo un it.
		while (it != states.begin()) {
			if (it != states.end()) {
				if (!it->second->IsTrasparent()) {
					break;
				}
			}
			--it;
		}
		for (; it != states.end(); ++it) {
			it->second->Draw(); //disegna il primo BaseState non trasparente
		}
	}
	else {
		states.back().second->Draw(); //disegna il BaseState relativo allo stato dal momento che è già non trasparente.
	}
}

/* Uguale al draw, ma invece di controllare la trasparenza controllo la trascendenza, 
che è la caratteristica di un oggetto di poter essere updatato oppure no */
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

/*controllo tra tutti gli stati se esiste un dato stato in input, controlla se è presente nello stack toRemove.
 in caso affermativo ritorna true altrimenti falso.*/
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
	//inserisce lo stato da rimuovere nella lista toRemove.
}

void StateManager::ProcessRequests() {
	while (toRemove.begin() != toRemove.end()) {
		RemoveState(*toRemove.begin()); // rimuove gli stati
		toRemove.erase(toRemove.begin()); // dealloca la memoria
	}
}

void StateManager::SwitchTo(const StateType& type) {
	shared->eventManager->SetCurrentState(type);	// setto il nuovo stato
	for (auto it = states.begin(); it != states.end(); it++) {
		// se trovo il tipo corrispondente
		if (it->first == type) {
			states.back().second->Deactivate(); // deattivo quello attuale
			StateType tmp_type = it->first;  
			BaseState* tmp_state = it->second;
			states.erase(it); //elimino lo stato per poi inserirlo in fondo (per il calcolo successivo)
			states.emplace_back(tmp_type, tmp_state); 
			tmp_state->Activate(); //attivo il nuovo BaseState.
			return;
		}
	}
	
	if (!states.empty()) {
		states.back().second->Deactivate(); 
	}
	//è necessario creare lo stato per inizializzare lo stato.
	CreateState(type);
	states.back().second->Activate();

}

void StateManager::CreateState(const StateType& type) {
	auto newState = stateFactory.find(type); //controllo se esiste uno stato registrato simile a questo inserito.
	if (newState == stateFactory.end()) return;
	BaseState* state = newState->second(); //assegno la memoria ritornata dalla funzione.
	states.emplace_back(type, state);
	state->OnCreate(); //dipende dall'implementazione interna della funzione in ciascuno stato. (BaseState è astratta)
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




