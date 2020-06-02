#pragma once
#include <SFML\System\Time.hpp>

class StateManager;

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
	StateManager* GetStateManager() {
		return stateManager;
	}
protected:
	bool transparent;
	bool transcendent;
	StateManager* stateManager;
};