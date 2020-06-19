#pragma once

#include "BaseState.h"
#include "EventManager.h"

class State_Paused : public BaseState {
public:
	State_Paused(StateManager* l_stateManager);
	~State_Paused();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void Unpause(EventDetails* details);

private:
	sf::Text text;
	sf::RectangleShape rect;
	sf::Font font;

};