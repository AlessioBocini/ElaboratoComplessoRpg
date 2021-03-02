

#include "GameManager.h"
#include <iostream>

bool GameManager::CheckForLevelUp() {

	return true;
}
bool GameManager::isButtonPressedSKill(std::string const& buttonPressed) const{
	return true;
}
bool GameManager::isGameOver() const {
	return GameOver;
}
bool GameManager::isGodMode() const
{
	return godmode;
}
bool GameManager::LoadGame() {
	return true;
}
bool GameManager::SaveGame() {
	return true;
}
void  GameManager::RegenStamina() {

}
void GameManager::RestartAchievementClock()
{
	clockAchievement.restart();
}
sf::Vector2i GameManager::GetSpriteSize() const
{
	return spriteSize;
}
bool GameManager::AggiungiSkill(Skill skill) {
	return true;
}

bool GameManager::isGamePaused() const{
	return isPaused;
}

void GameManager::SetInPauseGame(bool pause) {
	isPaused = pause;
}
void GameManager::SetGameOverGame(bool value)
{
	GameOver = value;
}
GameManager::GameManager() : m_window("rpg game", sf::Vector2u(1366, 720), false, context), world(context), spriteSize(32, 32), timeDisplayAchievement(3.5),diplayAchievement(false),entitymanager(context), achievementmanager(context), stateManager(context, this), isPaused(false), GameOver(false), isDebugMenuActive(false), isConcolePressed(false), assetmanager(context), textAchievement(sf::Text("", context.assetManager->GetFont("arial.ttf"))) {
	context.gameManager = this;
	Giocatore* player = entitymanager.GetGiocatore();
	
	context.gameMap = &world;
	context.wind = &m_window;
	context.eventManager = m_window.GetEventManager();
	context.assetManager = &assetmanager;
	context.entityManager = &entitymanager;
	stateManager.SwitchTo(StateType::Intro);
	background_song.openFromFile("assets/Music/Refrain.ogg");
	textFormula.setFont(assetmanager.GetFont("arial.ttf"));
	world.LoadMaps();
	world.SetPrevMap("map1");
	entitymanager.ConfigurePlayer();
	observer = std::unique_ptr<Observer>(new Observer(player->GetSubject(),context));
}

GameManager::~GameManager() {}

void GameManager::Update() {


	m_window.Update();
	stateManager.Update(elapsed);

	if (!isPaused) {
		world.getActualMap().Update(elapsed);
		entitymanager.Update(elapsed);
		achievementmanager.CheckAchievements();
		
	}

}

int GameManager::GetGodModeValue() const
{
	return godmodevalue;
}

void GameManager::SetPlayerStart(const sf::Vector2f& a) {
	entitymanager.GetGiocatore()->setSpawnPoint(a);
}

void GameManager::HandleInput() {
	/// <summary>
	/// 
	Giocatore* giocatore = entitymanager.GetGiocatore();
	Arma* arma = giocatore->GetInventario()->GetWeapon();
	Animator* animpg = giocatore->GetAnimpg();
	float speed = giocatore->GetVelocita();
	giocatore->SetRunning(false);
	/// </summary>
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
	
	if (!giocatore->isAlive()) {

		giocatore->Update(elapsed);
		if(giocatore->GetAnimpg()->GetCurrentFrame() == 3)
			context.gameManager->SetGameOverGame(true);
		return;
	}

	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (giocatore->GetInventario()->isInventoryVisibile()) {
			giocatore->GetInventario()->InterazioneSlot();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		giocatore->PreparaAttacco();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		giocatore->ToggleInventory();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		giocatore->PreparaInterazione();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {

		if (giocatore->GetStamina() != 0) {
			giocatore->SetRunning(true);
			speed *= 1.5;
		}
		else {
			giocatore->SetRunning(false);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
		
		if(arma != nullptr)
			arma->WeaponPosition('A');
		if (!giocatore->isBlockedA()) {
			if (animpg->GetCurrentAnimationName() != "animationA") {
				animpg->SwitchAnimation("animationA");
				if(arma != nullptr)
					arma->GetAnimpg()->SwitchAnimation("armaA");
			}
		
			giocatore->Movimento(-1 * speed, 0);

		}

		pressedkey = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
		if (arma != nullptr)
			arma->WeaponPosition('D');
		if (!giocatore->isBlockedD()) {
			if (animpg->GetCurrentAnimationName() != "animationD") {
				animpg->SwitchAnimation("animationD");
				if (arma != nullptr)
					arma->GetAnimpg()->SwitchAnimation("armaD");
			}
		
			giocatore->Movimento(speed, 0);
		}

		pressedkey = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (!giocatore->isBlockedW()) {
			if (animpg->GetCurrentAnimationName() != "animationW") {
				animpg->SwitchAnimation("animationW");
				if (arma != nullptr)
					arma->GetAnimpg()->SwitchAnimation("armaW");
			}
		
			giocatore->Movimento(0, -1 * speed);
		}

		pressedkey = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (!giocatore->isBlockedS()) {
			if (animpg->GetCurrentAnimationName() != "animationS")	{
				animpg->SwitchAnimation("animationS");
				if (arma != nullptr)
					arma->GetAnimpg()->SwitchAnimation("armaS");
			}
		
			giocatore ->Movimento(0, speed);
		}

		pressedkey = true;

	}
	if (!pressedkey) {
		
		if (animpg->GetCurrentAnimationName() == "animationA") {
			animpg->SwitchAnimation("animationIDLEA");
			if (arma != nullptr)
				arma->Reset("armaIDLEA");
		}
		else if (animpg->GetCurrentAnimationName() == "animationD") {
			animpg->SwitchAnimation("animationIDLED");
			if (arma != nullptr)
				arma->Reset("armaIDLED");
		}
		else if (animpg->GetCurrentAnimationName() == "animationS") {
			animpg->SwitchAnimation("animationIDLES");
		}
		else if (animpg->GetCurrentAnimationName() == "animationW") {
			animpg->SwitchAnimation("animationIDLEW");
		}
	}
	giocatore->Update(elapsed);
	

}

void GameManager::ApplyFormula() {
	std::cout << consoleFormula << std::endl;


	if (consoleFormula.substr(0, 8) == "shutdown") {
		std::cout << "il gioco si chiude" << std::endl;
	}
	if (consoleFormula.substr(0, 7) == "godmode") {
		auto giocatore = context.entityManager->GetGiocatore();
		if (!godmode) {
			std::cout << "god mode enabled" << std::endl;
			
			giocatore->SetVitalita(godmodevalue);
			giocatore->SetStamina(godmodevalue);
		}
		else {
			std::cout << "god mode disabled" << std::endl;

			giocatore->SetVitalita(giocatore->GetMaxVitalita());
			giocatore->SetStamina(giocatore->GetMaxStamina());

		}
		godmode = !(godmode);

	}
	else if (consoleFormula.substr(0, 8) == "teleport") {
		int k = 0;
		std::string x = "";
		std::string y = "";
		for (unsigned int i = 9; i < consoleFormula.length(); i++) {
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
			entitymanager.Add(EntityType::Enemy, "Scheletro", world.getActualMap().GetCurrentTerritory(),int(EnemyType::Skeleton));
		}
		else if (consoleFormula.length() > 7 && consoleFormula.substr(6, 8) == "miniboss") {
			std::cout << "- miniboss" << std::endl;
		}
	}
}
void GameManager::CommandConsole() {
	sf::Event ev;
	if (isConcolePressed) {
		sf::RenderWindow* renderwindow = m_window.GetRenderWindow();
		while (renderwindow->pollEvent(ev)) {
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

sf::Time GameManager::GetElapsed() const {
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



void GameManager::SetDisplayAchievement(bool value)
{
	diplayAchievement = value;
}

void GameManager::SetTextAchivement(std::string message)
{
	textAchievement.setString("Achievement : "+message);
}

void GameManager::DrawEntities() {

	float nametextweight = 0.5, infoweight = 0.25;
	Giocatore* player = entitymanager.GetGiocatore();
	
	
	if (world.GetPrevMap() == "map1") {

		sf::Text ShopTag("SHOP", assetmanager.GetFont("arial.ttf"));
		ShopTag.setScale(nametextweight * 2, nametextweight * 2);
		ShopTag.setOutlineColor(sf::Color::Black);
		ShopTag.setOutlineThickness(1);
		ShopTag.setPosition(10.25 * 32, 8.75 * 32);
		m_window.Draw(ShopTag);
		sf::Text GuildTag("GUILD", assetmanager.GetFont("arial.ttf"));
		GuildTag.setScale(nametextweight * 2, nametextweight * 2);
		GuildTag.setOutlineColor(sf::Color::Black);
		GuildTag.setOutlineThickness(1);
		GuildTag.setPosition(15.05f * 32.f, 8.75f * 32.f);
		m_window.Draw(GuildTag);
	}
	
	entitymanager.Draw();
}
void GameManager::DrawAchiement()
{

	float time = clockAchievement.getElapsedTime().asSeconds();
	if (diplayAchievement) {

		textAchievement.setPosition((m_window.GetViewSpace().left+m_window.GetViewSpace().width/2) , m_window.GetViewSpace().top +10);
		textAchievement.setFillColor(sf::Color::Yellow);
		textAchievement.setScale(0.8f, 0.8f);
		textAchievement.setOutlineColor(sf::Color::Black);
		textAchievement.setOutlineThickness(1);
		m_window.Draw(textAchievement);
	}

	if (time >= timeDisplayAchievement) {
		textAchievement.setString("");
		diplayAchievement = false;
	}

}
void GameManager::SetMaxFramerate(float limit) {
	sf::RenderWindow* renderWindow = m_window.GetRenderWindow();
	renderWindow->setFramerateLimit(limit);
	renderWindow->setVerticalSyncEnabled(true);
}