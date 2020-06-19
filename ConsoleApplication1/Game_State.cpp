
#include "StateManager.h"
#include "GameManager.h"
State_Game::State_Game(StateManager* l_stateManager) : BaseState(l_stateManager) , sprite(stateManager->GetContext()->gameManager->GetGiocatore().GetSprite()){}
State_Game::~State_Game() {}

void State_Game::OnCreate() {
	stateManager->GetContext()->gameManager->SetInPauseGame(false);
	EventManager* eventManag = stateManager->GetContext()->eventManager;
	eventManag->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	eventManag->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
}
void State_Game::OnDestroy() {
	EventManager* eventManag = stateManager->GetContext()->eventManager;
	eventManag->RemoveCallback(StateType::Game, "Key_Escape");
	eventManag->RemoveCallback(StateType::Game, "Key_P");
}

void State_Game::Update(const sf::Time& time) {
	//workaround della sprite.
	
}

//il giocatore dovrà essere mostrato solo ed esclusivamente durante lo stato di gioco.
void State_Game::Draw() {
	stateManager->GetContext()->gameMap->Draw();
	stateManager->GetContext()->wind->GetRenderWindow()->draw(stateManager->GetContext()->gameManager->GetGiocatore().GetSprite());
}

void State_Game::MainMenu(EventDetails* details) {
	stateManager->SwitchTo(StateType::MainMenu);
	// non viene rimosso per far si che sia possibile tornare al main menu
}

void State_Game::Pause(EventDetails* details) {
	stateManager->GetContext()->gameManager->SetInPauseGame(true);
	stateManager->SwitchTo(StateType::Paused);
	// non viene rimosso per far si che sia possibile rimettere in pausa il gioco.
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}