
#include "StateManager.h"
#include "GameManager.h"
State_Game::State_Game(StateManager* l_stateManager) : BaseState(l_stateManager), sprite(stateManager->GetContext()->entityManager->GetGiocatore()->GetSprite()) {}
State_Game::~State_Game() {}

void State_Game::OnCreate() {
	stateManager->GetContext()->gameManager->SetInPauseGame(false);
	EventManager* eventManag = stateManager->GetContext()->eventManager;
	eventManag->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
	eventManag->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
	sf::Vector2u size = stateManager->GetContext()->wind->GetwindowSize();
	view.setSize((float)size.x, (float)size.y);
	view.setCenter(size.x / 2, size.y / 2);
	view.zoom(0.6f);
	stateManager->GetContext()->wind->GetRenderWindow()->setView(view);
	sf::Music* song = stateManager->GetContext()->gameManager->GetBackGroundMusic();
	if (song) {
		song->play();
		song->setVolume(0);
		song->setLoop(true);
	}


}
void State_Game::OnDestroy() {
	EventManager* eventManag = stateManager->GetContext()->eventManager;
	eventManag->RemoveCallback(StateType::Game, "Key_Escape");
	eventManag->RemoveCallback(StateType::Game, "Key_P");
}

void State_Game::Update(const sf::Time& time) {
	//workaround della sprite.
	SharedContext* context = stateManager->GetContext();
	Giocatore* player = context->entityManager->GetGiocatore();
	view.setCenter(player->GetPosition());
	context->wind->GetRenderWindow()->setView(view);
	sf::FloatRect viewSpace = context->wind->GetViewSpace();
	if (viewSpace.left <= 0) {
		view.setCenter(viewSpace.width / 2, view.getCenter().y);
		context->wind->GetRenderWindow()->setView(view);
	}
	else if (viewSpace.left + viewSpace.width > (context->gameMap->GetMapSize().x + 1) * Sheet::Tile_Size) {
		view.setCenter(((context->gameMap->GetMapSize().x + 1) * Sheet::Tile_Size) - (viewSpace.width / 2), view.getCenter().y);
		context->wind->GetRenderWindow()->setView(view);
	}

	//context->gameMap->Update(time);
}

//il giocatore dovrà essere mostrato solo ed esclusivamente durante lo stato di gioco.
void State_Game::Draw() {
	auto base = stateManager->GetContext();
	base->gameMap->Draw();
	base->gameManager->DrawEntities();
	base->gameManager->DrawDebugMenu();
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