#include "Game_State.h"
#include "StateManager.h"
#include "GameManager.h"
State_Game::State_Game(StateManager* l_stateManager) : BaseState(l_stateManager) , sprite(stateManager->GetGameManager()->GetGiocatore().GetSprite()){}
State_Game::~State_Game() {}

void State_Game::OnCreate() {

	stateManager->GetGameManager()->SetInPauseGame(false);
	EventManager* eventManag = stateManager->GetContext()->eventManager;
	eventManag->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	eventManag->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
}
void State_Game::OnDestroy() {
	EventManager* eventManag = stateManager->GetContext()->eventManager;
	eventManag->RemoveCallback(StateType::Game, "Key_Escape");
	eventManag->RemoveCallback(StateType::Game, "Key_P");
}

void State_Game::Activate(){}
void State_Game::Deactivate(){}

void State_Game::Update(const sf::Time& time) {
	
}
void State_Game::Draw() {
	stateManager->GetContext()->wind->GetRenderWindow()->draw(stateManager->GetGameManager()->GetGiocatore().GetSprite());
}

void State_Game::MainMenu(EventDetails* details) {
	stateManager->SwitchTo(StateType::MainMenu);
}
void State_Game::Pause(EventDetails* details) {
	stateManager->GetGameManager()->SetInPauseGame(true);
	stateManager->SwitchTo(StateType::Paused);
}