
#include "StateManager.h"
#include "GameManager.h"
State_MainMenu::State_MainMenu(StateManager* l_stateManager) : BaseState(l_stateManager),buttonPadding(4){

}
State_MainMenu::~State_MainMenu(){}

void State_MainMenu::OnCreate() {
	stateManager->GetContext()->gameManager->SetInPauseGame(true);
	sf::Vector2u windowSize = stateManager->GetContext()->wind->GetRenderWindow()->getSize();
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setString(sf::String("Main Menu"));
	text.setCharacterSize(18);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,textRect.top+textRect.height/2.0f);
	text.setPosition(windowSize.x / 2.0f, 100);
	//text.setPosition(400, 100);
	buttonSize = sf::Vector2f(300.0f, 32.0f);
	buttonPos = sf::Vector2f(windowSize.x/2, 200.0f);
	buttonPadding = 4; //4px

	std::string str[3];
	str[0] = "PLAY";
	str[1] = "SAVE";
	str[2] = "QUIT";

	for (int i = 0; i < 3; ++i) {
		sf::Vector2f buttonPosition(buttonPos.x, buttonPos.y +
		(i * (buttonSize.y + buttonPadding)));
		rects[i].setSize(buttonSize);
		rects[i].setFillColor(sf::Color::Red);

		rects[i].setOrigin(buttonSize.x / 2.0f, buttonSize.y / 2.0f);
		rects[i].setPosition(buttonPosition);

		labels[i].setFont(font);
		labels[i].setString(sf::String(str[i]));
		labels[i].setCharacterSize(12);

		sf::FloatRect rect = labels[i].getLocalBounds();
		labels[i].setOrigin(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		labels[i].setPosition(buttonPosition);
	}

	EventManager* eventManag = stateManager->GetContext()->eventManager;
	eventManag->AddCallback(StateType::MainMenu, "Mouse_Left", &State_MainMenu::MouseClick, this);

}
void State_MainMenu::OnDestroy() {
	EventManager* eventManag = stateManager->GetContext()->eventManager;
	eventManag->RemoveCallback(StateType::MainMenu, "Mouse_Left");
}

void State_MainMenu::Activate() {
	if (stateManager->HasState(StateType::Game)
		&& labels[0].getString() == "PLAY")
	{
		labels[0].setString(sf::String("RESUME"));
		sf::FloatRect rect = labels[0].getLocalBounds();
		labels[0].setOrigin(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);
	}
}
void State_MainMenu::Deactivate(){}

void State_MainMenu::Update(const sf::Time& l_time){}


void State_MainMenu::Draw() {
	sf::RenderWindow* window = stateManager->GetContext()->wind->GetRenderWindow();
	window->draw(text);
	for (int i = 0; i < 3; i++) {
		window->draw(labels[i]);
	}
}
void State_MainMenu::MouseClick(EventDetails* l_details) {
	sf::Vector2i mousePos = l_details->mouse;

	float halfX = buttonSize.x / 2.0f;
	float halfY = buttonSize.y / 2.0f;
	for (int i = 0; i < 3; ++i) {
		if (mousePos.x >= rects[i].getPosition().x - halfX &&
			mousePos.x <= rects[i].getPosition().x + halfX &&
			mousePos.y >= rects[i].getPosition().y - halfY &&
			mousePos.y <= rects[i].getPosition().y + halfY)
		{
			if (i == 0) {
				stateManager->SwitchTo(StateType::Game);
			}
			else if (i == 1) {
				// Credits state.
			}
			else if (i == 2) {
				stateManager->GetContext()->wind->Close();
			}
		}
	}
}