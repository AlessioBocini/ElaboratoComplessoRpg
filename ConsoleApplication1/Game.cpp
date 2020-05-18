#include "Game.h"
#include "Animator.h"

//entita
void Entita::Attacco() {

}
void Entita::Movimento() {

}
// giocatore
void Giocatore::Attacco(std::string const& buttonPressed , bool isSkill){
}
bool Giocatore::Movimento(char const& buttonPressed) {
	bool isMovement = true;
	switch (buttonPressed)
	{
	case 'w': {
		
		GetSprite().move(0, -1*GetVelocita() );
		break;
	}
	case 's': {
		GetSprite().move(0,GetVelocita());
		break;
	}
	case 'd': {
		GetSprite().move(GetVelocita() , 0);
		break;
	}
	case 'a': {
		GetSprite().move(-1 * (GetVelocita()),0);
		
		break;
	}
	default:
		isMovement = false;
		break;
	}

	return isMovement;
}

bool Giocatore::EquipArmor(Armatura const& obj) {
	return true;
}
bool Giocatore::EquipWeapon(Arma const& obj) {
	return true;
}
bool Giocatore::Interazione(Entita const& ent) {
	return true;
}
// equipaggiamento

bool Inventario::EliminaOggetto(Equipaggiamento const& equip) {
	return true;
}
bool Inventario::AggiungiOggetto(Equipaggiamento const& equip) {
	return true;
}

// Mondo
bool Territorio::ShowMap() {
	return true;
}

// Window
Window::Window()
{
	Setup("Window", sf::Vector2u(640, 480),false);
}
Window::Window(const std::string title, const sf::Vector2u& size, bool fullscreen) {
	Setup(title, size, fullscreen);
}
Window::~Window() {
	Destroy();
}
void Window::Setup(const std::string title, const sf::Vector2u& size, bool fullscreen) {
	windowTitle = title;
	windowSize = size;
	isfullscreen = fullscreen;
	isdone = false;
	Create();
}
void Window::Create() {
	auto style = (isfullscreen == true ? sf::Style::Fullscreen : sf::Style::Default);
	window.create({ windowSize.x , windowSize.y, 32 }, windowTitle, style);
}
void Window::Destroy() {
	window.close();
}
void Window::Update() {
	sf::Event ev;
	while (window.pollEvent(ev)) {
		if (ev.type == sf::Event::Closed) {
			isdone = true;
		}
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::F5) {
			ToggleFullscreen();
		}
	}
}
void Window::ToggleFullscreen() {
	isfullscreen = !isfullscreen;
	Destroy();
	Create();
}
void Window::BeginDraw() {
	window.clear(sf::Color::Black);
}
void Window::EndDraw() {
	window.display();
}
bool Window::isDone() {
	return this->isdone;
}
bool Window::isFullscreen() {
	return this->isfullscreen;
}
sf::Vector2u Window::GetwindowSize() {
	return windowSize;
}
void Window::Draw(sf::Drawable& drawable) {
	window.draw(drawable);
}

// GameManager

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

GameManager::GameManager()  : m_window("rpg game", sf::Vector2u(800, 600), false) , player("alessio", sf::Vector2f(0, 0)), animpg(player.GetSprite()), spriteSize(32, 32) {
	
	player.GetSprite().setTextureRect(sf::IntRect(0, 0, spriteSize.x, spriteSize.y));
	animpg.SwitchAnimation("animationS");
}
GameManager::~GameManager(){}

void GameManager::Update() {
	m_window.Update();
}
void GameManager::HandleInput() {
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (animpg.GetCurrentAnimationName() != "animationA")
			animpg.SwitchAnimation("animationA");
		player.Movimento('a');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (animpg.GetCurrentAnimationName() != "animationD")
			animpg.SwitchAnimation("animationD");
		player.Movimento('d');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (animpg.GetCurrentAnimationName() != "animationW")
			animpg.SwitchAnimation("animationW");
		player.Movimento('w');
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (animpg.GetCurrentAnimationName() != "animationS")
			animpg.SwitchAnimation("animationS");
		player.Movimento('s');
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