#pragma once
#include "Animator.h"
#include "Window.h"
#include "Skill.h"
#include "Giocatore.h"
#include "AssetManager.h"
#include "StateManager.h"
#include "Mondo.h"
#include "EntityManager.h"


class GameManager {

public:

	sf::Vector2i spriteSize;
	GameManager();
	~GameManager();


	void HandleInput();
	void CommandConsole();
	void ApplyFormula();
	void Update();
	void LateUpdate();
	void Render();
	Window* getWindow();
	sf::Time GetElapsed();
	void RestartClock();


	bool isButtonPressedSKill(std::string const& buttonPressed);
	bool AggiungiSkill(Skill skill);
	void SetInPauseGame(bool value);
	bool isGamePaused();
	bool isGameOver();
	void SetPlayerStart(sf::Vector2f a);
	bool LoadGame();
	bool SaveGame();
	bool CheckForLevelUp();
	void RegenStamina();


	void ToggleDebugMenu();
	void DrawDebugMenu();

	sf::Music* GetBackGroundMusic() { return &background_song; }
	void SetBackGroundMusic(std::string const& filepath) {
		background_song.openFromFile(filepath);
	}


	void DrawEntities();
private:
	Window m_window;

	sf::Vector2f beginPlayerpos;
	bool isPaused;

	bool isDebugMenuActive;
	bool isConcolePressed;
	std::string consoleFormula;
	sf::Text textFormula;
	sf::RectangleShape console;

	AssetManager assetmanager;
	StateManager stateManager;
	EntityManager entitymanager;
	SharedContext context;
	sf::Music background_song;
	Mondo world;
	sf::Clock clock;
	sf::Time elapsed;

};