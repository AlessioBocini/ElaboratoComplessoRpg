#include "GameManager.h"

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

GameManager::GameManager() : m_window("rpg game", sf::Vector2u(800, 600), false), player("alessio", sf::Vector2f(0, 0)), animpg(player.GetSprite()), spriteSize(32, 32) {

	player.GetSprite().setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
	animpg.SwitchAnimation("animationS");
}
GameManager::~GameManager() {}

void GameManager::Update() {
	m_window.Update();
}



void GameManager::HandleInput() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (animpg.GetCurrentAnimationName() != "animationA")
			animpg.SwitchAnimation("animationA");
		player.Movimento(-1 * player.GetVelocita(), 0);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (animpg.GetCurrentAnimationName() != "animationD")
			animpg.SwitchAnimation("animationD");
		player.Movimento(player.GetVelocita(), 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (animpg.GetCurrentAnimationName() != "animationW")
			animpg.SwitchAnimation("animationW");
		
		player.Movimento(0, -1 * player.GetVelocita());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (animpg.GetCurrentAnimationName() != "animationS")
			animpg.SwitchAnimation("animationS");
		player.Movimento(0, player.GetVelocita());
	}
	animpg.update(elapsed);
}

void GameManager::Render() {
	m_window.BeginDraw();
	m_window.Draw(player.GetSprite());
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