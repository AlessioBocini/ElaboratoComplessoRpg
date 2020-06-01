#pragma once
#include "Animator.h"
#include "Window.h"
#include "Skill.h"
#include "Giocatore.h"
#include "AssetManager.h"


class GameManager {
private:

public:
	Animator animpg;
	sf::Vector2i spriteSize;
	GameManager();
	~GameManager();


	void HandleInput();
	void Update();
	void Render();
	Window* getWindow();
	sf::Time GetElapsed();
	void RestartClock();


	bool isButtonPressedSKill(std::string const& buttonPressed);
	bool AggiungiSkill(Skill skill);
	bool isGameOver();
	bool LoadGame();
	bool SaveGame();
	bool CheckForLevelUp();
	void RegenStamina();
private:
	Window m_window;

	Giocatore player;
	AssetManager assetmanager;

	sf::Clock clock;
	sf::Time elapsed;

};