
#include "StateManager.h"
#include "GameManager.h"


State_Paused::State_Paused(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_Paused::~State_Paused() {}

void State_Paused::OnCreate() {
	
	SetTransparent(true); // Set our transparency flag.
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setString(sf::String("PAUSED"));
	text.setCharacterSize(14);
	text.setStyle(sf::Text::Bold);
	stateManager->GetContext()->gameManager->SetInPauseGame(true);
	sf::Vector2u windowSize = stateManager->GetContext()->wind->GetRenderWindow()->getSize();

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	rect.setSize(sf::Vector2f(windowSize));
	rect.setPosition(0, 0);
	rect.setFillColor(sf::Color(0, 0, 0, 150));

	EventManager* eventmanag = stateManager->GetContext()->eventManager;
	eventmanag->AddCallback(StateType::Paused, "Key_P", &State_Paused::Unpause, this);
}

void State_Paused::OnDestroy() {
	EventManager* eventManag = stateManager->GetContext()->eventManager;
	eventManag->RemoveCallback(StateType::Paused, "Key_P");
}

void State_Paused::Draw() {
	sf::RenderWindow* wind = stateManager->GetContext()->wind->GetRenderWindow();
	wind->draw(rect);
	wind->draw(text);
}

void State_Paused::Unpause(EventDetails* l_details) {
	stateManager->GetContext()->gameManager->SetInPauseGame(false);
	stateManager->SwitchTo(StateType::Game);
}

void State_Paused::Activate() {}
void State_Paused::Deactivate() {}
void State_Paused::Update(const sf::Time& l_time) {}