

#include "GameManager.h"
#include <iostream>

bool GameManager::CheckForLevelUp() {

	return true;
}
bool GameManager::isButtonPressedSKill(std::string const& buttonPressed) {
	return true;
}
bool GameManager::isGameOver() {
	return false;
}
bool GameManager::LoadGame() {
	return true;
}
bool GameManager::SaveGame() {
	return true;
}
void  GameManager::RegenStamina() {

}
bool GameManager::AggiungiSkill(Skill skill) {
	return true;
}

bool GameManager::isGamePaused() {
	return isPaused;
}
void GameManager::SetInPauseGame(bool pause) {
	isPaused = pause;
}
Giocatore GameManager::GetGiocatore() {
	return player;
}
GameManager::GameManager() : m_window("rpg game", sf::Vector2u(1366, 720), false), world(&context),  animpg(player.GetSprite()), spriteSize(32, 32) , stateManager(&context,this), player("alessio",sf::Vector2f(0,0)), isPaused(false) {
	player.GetSprite().setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
	player.setContext(&context);
	context.gameMap = &world;
	context.wind = &m_window;
	context.eventManager = m_window.GetEventManager();
	context.gameManager = this;
	context.assetManager = &assetmanager;
	stateManager.SwitchTo(StateType::Intro);
	animpg.SwitchAnimation("animationS");
	
	world.LoadMap("D:/visualstudioprojects/ConsoleApplication1/assets/files/map1.txt");
	player.setSpawnPoint(world.GetPlayerStartpoint());
	
}
GameManager::~GameManager() {}


void GameManager::Update() {


	m_window.Update();
	stateManager.Update(elapsed);
	player.CheckCollisions(&context);
	player.ResolveCollisions(&context);
	if (!isPaused) {
		world.Update(elapsed);

	}
		
}


void GameManager::HandleInput() {

	bool pressedkey = false;
	if (isPaused) return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (animpg.GetCurrentAnimationName() != "animationA")
			animpg.SwitchAnimation("animationA");
		if (!player.isblockedA) {
			player.Movimento(-1 * player.GetVelocita(), 0);
		
		}
			
		pressedkey = true;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (animpg.GetCurrentAnimationName() != "animationD")
			animpg.SwitchAnimation("animationD");
		if (!player.isblockedD) {
			player.Movimento(player.GetVelocita(), 0);
		}
			
		pressedkey = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (animpg.GetCurrentAnimationName() != "animationW")
			animpg.SwitchAnimation("animationW");

		if (!player.isblockedW) {
			player.Movimento(0, -1 * player.GetVelocita());
		}
			
		pressedkey = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (animpg.GetCurrentAnimationName() != "animationS")
			animpg.SwitchAnimation("animationS");

		if (!player.isblockedS) {
			player.Movimento(0, player.GetVelocita());
		}
			
		pressedkey = true;

	}
	if (pressedkey) {
		
		animpg.update(elapsed);
	}
		
	
}

void GameManager::Render() {
	m_window.BeginDraw();
	stateManager.Draw();
	
	m_window.EndDraw();
}

Window* GameManager::getWindow() {
	return &(this->m_window);
}

sf::Time GameManager::GetElapsed() {
	return elapsed;
}
void GameManager::RestartClock() {
	elapsed = clock.restart();
}

void GameManager::LateUpdate() {
	stateManager.ProcessRequests();
	RestartClock();
}