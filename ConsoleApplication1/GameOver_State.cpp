#include "StateManager.h"
#include "GameManager.h"

GameOver_State::GameOver_State(StateManager* l_stateManager) : BaseState(l_stateManager) {}

GameOver_State::~GameOver_State() {}

void GameOver_State::OnCreate() {
	stateManager->GetContext()->gameManager->SetInPauseGame(true);
	timePassed = 0.0f;
	sf::Vector2u windowSize = stateManager->GetContext()->wind->GetRenderWindow()->getSize();
	gameoverTexture.loadFromFile("assets/images/pack/System/GameOver.png");
	gameoverSprite.setTexture(gameoverTexture);
	gameoverSprite.setOrigin(gameoverTexture.getSize().x / 2.0f, gameoverTexture.getSize().y / 2.0f);
	gameoverSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setString("Premi spazio per continuare");
	text.setCharacterSize(15);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	EventManager* eventmanager = stateManager->GetContext()->eventManager;
	eventmanager->AddCallback(StateType::GameOver, "Intro_Continue", &GameOver_State::Continue, this);
}

void GameOver_State::OnDestroy() {
	EventManager* eventmanager = stateManager->GetContext()->eventManager;
	eventmanager->RemoveCallback(StateType::GameOver, "Intro_Continue");
}

void GameOver_State::Update(const sf::Time& time) {
	if (timePassed < 5.0f) {
		timePassed += time.asSeconds();
		gameoverSprite.setPosition(gameoverSprite.getPosition().x, gameoverSprite.getPosition().y + (48 * time.asSeconds()));
	}
}

void GameOver_State::Draw() {
	sf::RenderWindow* window = stateManager->GetContext()->wind->GetRenderWindow();
	window->draw(gameoverSprite);
	if (timePassed >= 5.0f) {
		window->draw(text);
	}
}

void GameOver_State::Continue(EventDetails* l_details) {
	if (timePassed >= 5.0f) {
		stateManager->GetContext()->gameManager->SetGameOverGame(false); 
		//stateManager->SwitchTo(StateType::); 
		stateManager->Remove(StateType::GameOver); 
		stateManager->GetContext()->wind->Close();
	}
}

void GameOver_State::Activate() {}
void GameOver_State::Deactivate() {}