#pragma once
#include <SFML\System\Time.hpp>
#include "Window.h"
class StateManager; //faccio una forward declaration. inoltre il Base State non ha bisogno di conoscere niente di StateManager.
					// inoltre mi serve per evitare una definizione ricorsiva dello state manager (al suo interno contiene BaseState)

class BaseState {
	friend class StateManager;
public:
	BaseState(StateManager* stateManager) : stateManager(stateManager), transparent(false), transcendent(false){}
	virtual ~BaseState(){}

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;

	virtual void Update(const sf::Time& time) = 0;
	virtual void Draw() = 0;
	
	void SetTransparent(const bool& isTrasparent) {
		transparent = isTrasparent;
	}
	bool IsTrasparent() const {
		return transparent;
	}
	void SetTranscendent(const bool& isTrascendent) {
		transcendent = isTrascendent;
	}

	bool IsTranscendent() const {
		return transcendent;
	}
	sf::View& GetView() { return view; }
	StateManager* GetStateManager() {
		return stateManager;
	}
protected:
	bool transparent;
	bool transcendent;
	StateManager* stateManager;
	sf::View view;
};