
#include "Inventario.h"
#include "GameManager.h"
bool Inventario::EliminaOggetto(Equipaggiamento const& equip) {
	return true;
}
bool Inventario::AggiungiOggetto(Equipaggiamento const& equip) {
	return true;
}
void Inventario::ConfiguraEquip() {
	///Inventario UI
	/// 
	/// 
	/// 
	auto& inventoryAnim = this->animpg.CreateAnimation("inventory", "../assets/images/inventoryfull.png", sf::seconds(1), true);
	inventoryAnim.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(330, 245), 1);
	this->animations.push_back(inventoryAnim);
	this->animpg.SwitchAnimation("inventory");

	auto& moneta = this->animpgMoneta.CreateAnimation("moneta", "../assets/images/sheet.png", sf::seconds(1), true);
	moneta.AddFrames(sf::Vector2i(0, 16), sf::Vector2i(16, 16), 1);
	this->animationsMoneta.push_back(moneta);
	this->animpgMoneta.SwitchAnimation("moneta");

	/// WEAPON
	/// 
	/// 
	Animator* animpg = arma.GetAnimpg();
	int width = 58, height = 12;
	auto& animA = animpg->CreateAnimation("armaA", "../assets/images/pack/Weapons/test1.png", sf::seconds(1), true);
	animA.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(width, height), 3);
	arma.GetAnimations().push_back(animA);

	auto& animidleA = animpg->CreateAnimation("armaIDLEA", "../assets/images/pack/Weapons/test1.png", sf::seconds(1), true);
	animidleA.AddFrames(sf::Vector2i(width, 0), sf::Vector2i(width, height), 1);
	arma.GetAnimations().push_back(animidleA);

	auto& animD = animpg->CreateAnimation("armaD", "../assets/images/pack/Weapons/test2.png", sf::seconds(1), true);
	animD.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(width, height), 3);
	arma.GetAnimations().push_back(animD);
	auto& animIDLED = animpg->CreateAnimation("armaIDLED", "../assets/images/pack/Weapons/test2.png", sf::seconds(1), true);
	animIDLED.AddFrames(sf::Vector2i(width, 0), sf::Vector2i(width, height), 1);
	arma.GetAnimations().push_back(animIDLED);


	animpg->SwitchAnimation("armaS");
}
void Inventario::DrawInventory()
{
	if (!isVisible) return;
	//se è visibile allora posso mostrarlo
	sprite.setPosition(context.wind->GetViewSpace().left -8 , context.wind->GetViewSpace().top + (context.wind->GetViewSpace().height) - 245);
	invetoryMenutitle.setFillColor(sf::Color::White);
	invetoryMenutitle.setScale(1.0f, 1.0f);
	invetoryMenutitle.setOutlineThickness(1);
	invetoryMenutitle.setOutlineColor(sf::Color::Black);
	invetoryMenutitle.setPosition(sprite.getPosition().x +16, sprite.getPosition().y +1);
	moneta.setPosition(context.wind->GetViewSpace().left +298 - 32, context.wind->GetViewSpace().top + (context.wind->GetViewSpace().height) - 32 );
	
	denaroText.setString(std::to_string(denaro));
	denaroText.setPosition(context.wind->GetViewSpace().left + 160, context.wind->GetViewSpace().top + (context.wind->GetViewSpace().height) -32);
	denaroText.setFillColor(sf::Color::Black);
	denaroText.setScale(0.5f, 0.5f);
	context.wind->Draw(sprite); //inventario
	context.wind->Draw(invetoryMenutitle); //titolo
	context.wind->Draw(moneta); // icona moneta
	context.wind->Draw(denaroText); // numero denaro
}
void Inventario::DrawItems() {
	context.wind->Draw(arma.GetSprite());
}
void Inventario::UpdateItems(sf::Time const& dt) {
	
	Giocatore* giocatore = context.entityManager->GetGiocatore();
	float widthWeap = arma.GetSprite().getGlobalBounds().width;
	float heightWeap = arma.GetSprite().getGlobalBounds().height;
	float playerWidth = giocatore->GetSprite().getGlobalBounds().width;
	float playerHeight = giocatore->GetSprite().getGlobalBounds().height;
	char direction = giocatore->GetLastDirection();
	
	arma.GetAnimpg()->update(dt);
	//se inventario è visibile
	if (isVisible) {
		animpg.update(dt);
		animpgMoneta.update(dt);
	}
		
}
void Inventario::setContext(SharedContext& context) {
	this->context = context;
}

bool Inventario::isInventoryVisibile()
{
	return isVisible;
}

void Inventario::ToggleVisibility()
{
	isVisible = !(isVisible); //setta l'inventario visibile
	sf::sleep(sf::seconds(0.1f));
}

void Inventario::AddDenaro(int den)
{
	denaro += den;
}

void Inventario::DecreaseDenaro(int den)
{
	denaro -= den;
}

int Inventario::GetDenaro()
{
	return denaro;
}

bool Inventario::InterazioneSlot()
{
	sf::Mouse mouse = sf::Mouse();
	
	int posX = floor(((mouse.getPosition().x - context.wind->GetRenderWindow()->getPosition().x) / 32));// bordo sinistro schermo  - bordo sinistro finestra 
	int posY = floor((mouse.getPosition().y - context.wind->GetRenderWindow()->getPosition().y) / 32); // bordo in alto schermo - bordo in alto finestra
	// mi interessano i "blocchetti" quindi divido per 32

	//fisso le coordinate di inizio e fine inventario
	int initX = 7, initY = 13;
	int endX = 15, endY = 21;

	//casi di debug (fuori dall'area stabilita)
	if (posX > endX) return false;
	if (posX < initX) return false;
	if (posY < initY) return false;
	if (posY > endY) return false;

	// siccome il vettore [] [] [] [] [] [] [] usa indici partendo da 0 : 
	int diffX = posX - initX;
	int diffY = posY - initY;
	//siccome ci sono coppie di numeri: 
	diffX /= 2;
	diffY /= 2;
	
	//devo identificare univocamente ciascuno slot: 
	int Hashcode = diffX + diffY * 4;

	if (slot.size() < Hashcode + 1) {
		//caso di uscita nello slot che premo non c'è nulla
		// in generale quindi l'inventario (vettore di slot) è sortato
	}
	std::cout << Hashcode << std::endl;
	return true;
}
