#pragma once
#include "Animator.h"
#include "Window.h"
#include "Skill.h"
#include "AssetManager.h"
#include "StateManager.h"
#include "Mondo.h"
#include "EntityManager.h"
#include "Window.h"
#include "Observer.h"
#include "Giocatore.h"
#include "AchievementManager.h"
#include "MovementStrategy.h"
class GameManager {

public:

	
	GameManager();
	~GameManager();


	void HandleInput();
	void CommandConsole();
	void ApplyFormula();
	void Update();
	void LateUpdate();
	void Render();
	Window* getWindow();
	sf::Time GetElapsed() const;
	void RestartClock();
	Context<MovementStrategy> GetFollowContext() const { return FollowContext; }

	bool isButtonPressedSKill(std::string const& buttonPressed) const;
	bool AggiungiSkill(Skill skill);
	void SetInPauseGame(bool value);
	void SetGameOverGame(bool value);
	bool isGamePaused() const;
	bool isGameOver() const;
	void SetPlayerStart(const sf::Vector2f &a);
	bool LoadGame();
	bool SaveGame();
	bool CheckForLevelUp();
	void RegenStamina();
	void RestartAchievementClock();

	sf::Vector2i GetSpriteSize() const;

	void ToggleDebugMenu();
	void DrawDebugMenu();

	sf::Music* GetBackGroundMusic() { return &background_song; }
	void SetBackGroundMusic(std::string const& filepath) {
		background_song.openFromFile(filepath);
	}

	void SetDisplayAchievement(bool value);
	void SetTextAchivement(std::string message);
	void DrawEntities();
	void DrawAchiement();
	void SetMaxFramerate(float limit);
private:
	Window m_window;
	AchievementManager achievementmanager;
	sf::Vector2f beginPlayerpos;
	bool isPaused;
	bool GameOver;
	sf::Vector2i spriteSize;
	bool isDebugMenuActive;
	bool isConcolePressed;
	std::string consoleFormula;
	sf::Text textFormula;
	sf::RectangleShape console;


	Context<MovementStrategy> FollowContext;
	AssetManager assetmanager;
	StateManager stateManager;
	EntityManager entitymanager;
	SharedContext context;
	sf::Music background_song;
	Mondo world;
	
	sf::Text textAchievement;
	bool diplayAchievement;
	sf::Clock clockAchievement;
	float timeDisplayAchievement;
	std::unique_ptr<Observer> observer;

	

	sf::Clock clock;
	sf::Time elapsed;
	//Debug modes
	bool godmode = false;

};
