#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState {
public:
	State_Intro(StateManager* l_stateManager);
	~State_Intro();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void Continue(EventDetails* details);
private:
	sf::Texture introTexture;
	sf::Sprite introSprite;
	sf::Text text;
	sf::Font font;
	float timePassed;
};