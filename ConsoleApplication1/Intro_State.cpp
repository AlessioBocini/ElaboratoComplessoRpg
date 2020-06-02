#include "Intro_State.h"
#include "StateManager.h"
State_Intro::State_Intro(StateManager* l_stateManager): BaseState(l_stateManager) {}

State_Intro::~State_Intro() {}

void State_Intro::OnCreate() {
	timePassed = 0.0f;
	sf::Vector2u windowSize = stateManager->GetContext()->wind->GetRenderWindow()->getSize();
	introTexture.loadFromFile("intro.png");
	introSprite.setTexture(introTexture);
	introSprite.setOrigin(introTexture.getSize().x / 2.0f, introTexture.getSize().y / 2.0f);
	introSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setString("Premi spazio per continuare");
	text.setCharacterSize(15);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,textRect.top+textRect.height/2.0f);
	text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);
	EventManager* eventmanager = stateManager->GetContext()->eventManager;
	eventmanager->AddCallback(StateType::Intro, "Intro_Continue", &State_Intro::Continue, this);
}

void State_Intro::OnDestroy() {
	EventManager* eventmanager = stateManager->GetContext()->eventManager;
	eventmanager->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void State_Intro::Update(const sf::Time& time) {
	if (timePassed < 5.0f) {
		timePassed += time.asSeconds();
		introSprite.setPosition(introSprite.getPosition().x, introSprite.getPosition().y + (48 * time.asSeconds()));
	}
}

void State_Intro::Draw() {
	sf::RenderWindow* window = stateManager->GetContext()->wind->GetRenderWindow();
	window->draw(introSprite);
	if (timePassed >= 5.0f) {
		window->draw(text);
	}
}

void State_Intro::Continue(EventDetails* l_details) {
	if (timePassed >= 5.0f) {
		stateManager->SwitchTo(StateType::MainMenu);
		stateManager->Remove(StateType::Intro);
	}
}

void State_Intro::Activate() {}
void State_Intro::Deactivate() {}