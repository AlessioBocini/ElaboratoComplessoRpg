#pragma once
#include "Animator.h"
#include "Window.h"
#include "Skill.h"
#include "Giocatore.h"
#include "AssetManager.h"
#include "StateManager.h"


class GameManager {
private:

public:
	Animator animpg;
	sf::Vector2i spriteSize;
	GameManager();
	~GameManager();


	void HandleInput();
	void Update();
	void LateUpdate();
	void Render();
	Window* getWindow();
	sf::Time GetElapsed();
	void RestartClock();
	Giocatore GetGiocatore();

	bool isButtonPressedSKill(std::string const& buttonPressed);
	bool AggiungiSkill(Skill skill);
	void SetInPauseGame(bool value); 
	bool isGamePaused();
	bool isGameOver();
	bool LoadGame();
	bool SaveGame();
	bool CheckForLevelUp();
	void RegenStamina();

private:
	Window m_window;

	Giocatore player;

	bool isPaused;

	AssetManager assetmanager;
	StateManager stateManager;
	SharedContext context;
	sf::Clock clock;
	sf::Time elapsed;

};