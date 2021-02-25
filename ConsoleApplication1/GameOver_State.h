#pragma once
#include "BaseState.h"
#include "EventManager.h"

class GameOver_State : public BaseState {
public:
	GameOver_State(StateManager* l_stateManager);
	~GameOver_State();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void Continue(EventDetails* details);
private:
	sf::Texture gameoverTexture;
	sf::Sprite gameoverSprite;
	sf::Text text;
	sf::Font font;
	float timePassed;
};