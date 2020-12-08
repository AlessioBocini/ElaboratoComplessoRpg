

#include "GameManager.h"
#include <iostream>

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

bool GameManager::isGamePaused() {
	return isPaused;
}

void GameManager::SetInPauseGame(bool pause) {
	isPaused = pause;
}
GameManager::GameManager() : m_window("rpg game", sf::Vector2u(1366, 720), false), world(&context), spriteSize(32, 32), entitymanager(&context), stateManager(&context, this), isPaused(false), isDebugMenuActive(false), isConcolePressed(false) {

	auto player = entitymanager.GetGiocatore();
	context.gameMap = &world;
	context.wind = &m_window;
	context.eventManager = m_window.GetEventManager();
	context.gameManager = this;
	context.assetManager = &assetmanager;
	context.entityManager = &entitymanager;
	stateManager.SwitchTo(StateType::Intro);
	background_song.openFromFile("../assets/Music/Refrain.ogg");
	textFormula.setFont(assetmanager.GetFont("arial.ttf"));
	world.LoadMap("map1", true);
	world.SetPrevMap("map1");
	entitymanager.ConfigurePlayer();
	player->setContext(&context);
	player->setSpawnPoint(world.GetPlayerStartpoint());


}
GameManager::~GameManager() {}


void GameManager::Update() {


	m_window.Update();
	stateManager.Update(elapsed);

	if (!isPaused) {
		world.Update(elapsed);
		entitymanager.Update(elapsed);
	}

}

void GameManager::SetPlayerStart(sf::Vector2f a) {
	entitymanager.GetGiocatore()->setSpawnPoint(a);
}

void GameManager::HandleInput() {

	bool pressedkey = false;
	sf::Event ev;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) ToggleDebugMenu();
	if (isDebugMenuActive) {
		if (isConcolePressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				sf::sleep(sf::seconds(0.2f));
				ApplyFormula();
				isConcolePressed = false;
				consoleFormula = "";
				textFormula.setString("");
			}
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				sf::sleep(sf::seconds(0.2f));
				isConcolePressed = true;
			}
		}
	}

	if (isConcolePressed) return;
	if (isPaused) return;



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		if (entitymanager.GetGiocatore()->animpg.GetCurrentAnimationName() != "animationA")
			entitymanager.GetGiocatore()->animpg.SwitchAnimation("animationA");
		if (!entitymanager.GetGiocatore()->isblockedA) {
			entitymanager.GetGiocatore()->Movimento(-1 * entitymanager.GetGiocatore()->GetVelocita(), 0);

		}

		pressedkey = true;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (entitymanager.GetGiocatore()->animpg.GetCurrentAnimationName() != "animationD")
			entitymanager.GetGiocatore()->animpg.SwitchAnimation("animationD");
		if (!entitymanager.GetGiocatore()->isblockedD) {
			entitymanager.GetGiocatore()->Movimento(entitymanager.GetGiocatore()->GetVelocita(), 0);
		}

		pressedkey = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (entitymanager.GetGiocatore()->animpg.GetCurrentAnimationName() != "animationW")
			entitymanager.GetGiocatore()->animpg.SwitchAnimation("animationW");

		if (!entitymanager.GetGiocatore()->isblockedW) {
			entitymanager.GetGiocatore()->Movimento(0, -1 * entitymanager.GetGiocatore()->GetVelocita());
		}

		pressedkey = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (entitymanager.GetGiocatore()->animpg.GetCurrentAnimationName() != "animationS")
			entitymanager.GetGiocatore()->animpg.SwitchAnimation("animationS");

		if (!entitymanager.GetGiocatore()->isblockedS) {
			entitymanager.GetGiocatore()->Movimento(0, entitymanager.GetGiocatore()->GetVelocita());
		}

		pressedkey = true;

	}

	if (pressedkey) {
		entitymanager.GetGiocatore()->animpg.update(elapsed);
	}

}

void GameManager::ApplyFormula() {
	std::cout << consoleFormula << std::endl;


	if (consoleFormula.substr(0, 8) == "shutdown") {
		std::cout << "il gioco si chiude" << std::endl;
	}
	else if (consoleFormula.substr(0, 8) == "teleport") {
		int k = 0;
		std::string x = "";
		std::string y = "";
		for (int i = 9; i < consoleFormula.length(); i++) {
			while(i< consoleFormula.length() && consoleFormula[i] != ' ') {
				if (k == 0) {
					x += consoleFormula[i];
				}
				if (k == 1) {
					y += consoleFormula[i];
				}
				i++;
			}
			k++;
		}
		int xn = std::atoi(x.c_str());
		int yn = std::atoi(y.c_str());
		entitymanager.GetGiocatore()->SetPosition(sf::Vector2f(xn * Sheet::Tile_Size, yn * Sheet::Tile_Size));
		entitymanager.GetGiocatore()->GetSprite().setPosition(xn * Sheet::Tile_Size, yn * Sheet::Tile_Size);
		
	}
	else if (consoleFormula.substr(0, 5) == "spawn") {
		std::cout << "il gioco spawna un entita" << std::endl;

		if (consoleFormula.length() >= 7 && consoleFormula.substr(6, 3) == "npc") {
			std::cout << "- npc" << std::endl;
		}
		else if (consoleFormula.length() > 7 && consoleFormula.substr(6, 5) == "enemy") {
			std::cout << "- nemico comune" << std::endl;
			entitymanager.Add(EntityType::Enemy, "nemico1");
		}
		else if (consoleFormula.length() > 7 && consoleFormula.substr(6, 8) == "miniboss") {
			std::cout << "- miniboss" << std::endl;
		}
	}
}
void GameManager::CommandConsole() {
	sf::Event ev;
	if (isConcolePressed) {

		while (m_window.GetRenderWindow()->pollEvent(ev)) {
			if (ev.type == sf::Event::TextEntered) {
				if (ev.text.unicode == 8) {
					if (consoleFormula.length() != 0)
						consoleFormula.resize(consoleFormula.length() - 1);
				}
				else {
					if (consoleFormula.length() < 60 && ev.text.unicode != 13)
						consoleFormula += ev.text.unicode;
				}

				textFormula.setString(consoleFormula);
			}
		}
	}
}
void GameManager::ToggleDebugMenu() {
	if (isDebugMenuActive) {
		isConcolePressed = false;
		consoleFormula = "";
		textFormula.setString("");
	}
	isDebugMenuActive = !(isDebugMenuActive);

	sf::sleep(sf::seconds(0.1f));
}

void GameManager::Render() {
	m_window.BeginDraw();
	stateManager.Draw();

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

void GameManager::LateUpdate() {
	stateManager.ProcessRequests();
	RestartClock();
}

void GameManager::DrawDebugMenu() {
	if (!isDebugMenuActive) return;

	sf::RectangleShape debugmenu = sf::RectangleShape(sf::Vector2f(700, 110));
	debugmenu.setPosition(m_window.GetViewSpace().left, m_window.GetViewSpace().top + m_window.GetViewSpace().height * 0.75f);
	debugmenu.setOutlineColor(sf::Color::Yellow);
	debugmenu.setOutlineThickness(1.5);
	debugmenu.setFillColor(sf::Color(220, 220, 220));

	sf::Text debugmenutitle = sf::Text("Debug Menu", assetmanager.GetFont("arial.ttf"));
	debugmenutitle.setFillColor(sf::Color::Black);
	debugmenutitle.setScale(0.7f, 0.7f);
	debugmenutitle.setPosition(debugmenu.getPosition().x, debugmenu.getPosition().y);

	console = sf::RectangleShape(sf::Vector2f(500, 20));
	console.setOutlineThickness(1);
	console.setFillColor(sf::Color::White);
	console.setOutlineColor(sf::Color::Black);
	console.setPosition(debugmenu.getPosition().x + 5, debugmenu.getPosition().y + 50);
	m_window.Draw(debugmenu);
	m_window.Draw(debugmenutitle);
	m_window.Draw(console);

	textFormula.setScale(0.4f, 0.4f);
	textFormula.setFillColor(sf::Color::Black);
	textFormula.setPosition(console.getPosition().x + 5, console.getPosition().y);
	m_window.Draw(textFormula);
}


void GameManager::DrawEntities() {

	float nametextweight = 0.5, infoweight = 0.25;
	auto player = entitymanager.GetGiocatore();
	m_window.Draw(player->GetSprite());
	sf::Text name(player->GetNome(), assetmanager.GetFont("arial.ttf"));
	sf::Text level("[" + std::to_string(player->GetLivello()) + "]", assetmanager.GetFont("arial.ttf"));
	sf::Text vitalita("HP: " + std::to_string(player->GetVitalita()) + "%", assetmanager.GetFont("arial.ttf"));
	sf::Text stamina("SP: " + std::to_string(player->GetStamina()) + "%", assetmanager.GetFont("arial.ttf"));
	sf::Text coords("x : " + std::to_string(player->GetPosition().x/32) + "\ny : " + std::to_string(player->GetPosition().y/32), assetmanager.GetFont("arial.ttf"));
	
	name.setScale(nametextweight, nametextweight);
	name.setOutlineColor(sf::Color::Black);
	name.setOutlineThickness(1);
	level.setScale(nametextweight, nametextweight);
	level.setOutlineColor(sf::Color::Black);
	level.setOutlineThickness(1);
	stamina.setScale(infoweight, infoweight);
	stamina.setOutlineColor(sf::Color::Black);
	stamina.setOutlineThickness(0.25);
	vitalita.setScale(infoweight, infoweight);
	vitalita.setOutlineColor(sf::Color::Black);
	vitalita.setOutlineThickness(0.25);
	coords.setScale(nametextweight, nametextweight);
	coords.setFillColor(sf::Color::Red);
	
	

	coords.setPosition(m_window.GetViewSpace().left,m_window.GetViewSpace().top);
	name.setPosition(player->GetPosition().x - (player->GetSprite().getGlobalBounds().width) / 4 - 15, player->GetPosition().y - player->GetSprite().getGlobalBounds().height);
	vitalita.setPosition(player->GetPosition().x - (player->GetSprite().getGlobalBounds().width) / 4 - 15, player->GetPosition().y - player->GetSprite().getGlobalBounds().height / 3);
	stamina.setPosition(player->GetPosition().x + (player->GetSprite().getGlobalBounds().width) - 1 / 4 - 15, player->GetPosition().y - player->GetSprite().getGlobalBounds().height / 3);
	level.setPosition(player->GetPosition().x + 1.4f * (player->GetSprite().getGlobalBounds().width) - 15, player->GetPosition().y - player->GetSprite().getGlobalBounds().height);
	
	m_window.Draw(name);
	m_window.Draw(level);
	m_window.Draw(vitalita);
	m_window.Draw(stamina);
	m_window.Draw(coords);
	
	if (world.GetPrevMap() == "map1") {

		sf::Text ShopTag("SHOP", assetmanager.GetFont("arial.ttf"));
		ShopTag.setScale(nametextweight * 2, nametextweight * 2);
		ShopTag.setOutlineColor(sf::Color::Black);
		ShopTag.setOutlineThickness(1);
		ShopTag.setPosition(10.25 * 32, 8.75 * 32);
		m_window.Draw(ShopTag);
	}
	// MOCK MOVEMENT FOR Enemies
	for (auto i : entitymanager.getEntities()) {
		m_window.Draw(i->GetSprite());

		auto* ps = dynamic_cast<Miniboss*>(i);
		if (!(ps == nullptr)) {
			std::cout << "i'm a boss" << std::endl;
		}
	}

	for (auto i : entitymanager.getNpcs()) {
		if(i->getMap() == context.gameMap->GetPrevMap())
			m_window.Draw(i->GetSprite());
	}
}