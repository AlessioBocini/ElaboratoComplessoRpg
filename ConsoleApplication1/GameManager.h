#pragma once
#include "Animator.h"
#include "Window.h"
#include "Skill.h"
#include "Giocatore.h"
#include "AssetManager.h"
#include "StateManager.h"
#include "Mondo.h"

class GameManager {

public:
	
	Animator animpg;
	sf::Sprite mockrect;
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
	
	sf::Vector2f beginPlayerpos;
	bool isPaused;

	AssetManager assetmanager;
	StateManager stateManager;
	SharedContext context;
	Mondo world;
	sf::Clock clock;
	sf::Time elapsed;

};