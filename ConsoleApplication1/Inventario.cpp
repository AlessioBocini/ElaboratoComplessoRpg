
#include "Inventario.h"
#include "GameManager.h"
bool Inventario::EliminaOggetto(Equipaggiamento& equip) {
	// TODO REMOVE equipment using this function not statically
	return true;
}
bool Inventario::AggiungiOggetto(Equipaggiamento& equip, int value) {
	// TODO ADD equipment using this function not statically
	// Imagine i have the pointer Arma*
	auto ps = static_cast<Arma*>(&equip);
	if (ps == nullptr) {
		//armatura

	}
	else {
		//arma

		Arma* weap = new Arma(equip.GetNomeEquip(),equip.GetIcon(),equip.GetIconActivated(),value,context);

		this->equip.push_back(weap);

		Animator* animpg = weap->GetAnimpg();

		int width = 58, height = 12;
		auto& animA = animpg->CreateAnimation("armaA", "../assets/images/pack/Weapons/test1.png", sf::seconds(1), true);
		animA.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(width, height), 3);
		weap->GetAnimations().push_back(animA);

		auto& animidleA = animpg->CreateAnimation("armaIDLEA", "../assets/images/pack/Weapons/test1.png", sf::seconds(1), true);
		animidleA.AddFrames(sf::Vector2i(width, 0), sf::Vector2i(width, height), 1);
		weap->GetAnimations().push_back(animidleA);

		auto& animD = animpg->CreateAnimation("armaD", "../assets/images/pack/Weapons/test2.png", sf::seconds(1), true);
		animD.AddFrames(sf::Vector2i(0, 0), sf::Vector2i(width, height), 3);
		weap->GetAnimations().push_back(animD);
		auto& animIDLED = animpg->CreateAnimation("armaIDLED", "../assets/images/pack/Weapons/test2.png", sf::seconds(1), true);
		animIDLED.AddFrames(sf::Vector2i(width, 0), sf::Vector2i(width, height), 1);
		weap->GetAnimations().push_back(animIDLED);

		auto& animS = animpg->CreateAnimation("armaS", "../assets/images/pack/Characters/deathanimations.png", sf::seconds(1), true);
		animS.AddFrames(sf::Vector2i(0, Tile_Size), sf::Vector2i(Tile_Size, Tile_Size), 1);
		weap->GetAnimations().push_back(animS);

		auto& animW = animpg->CreateAnimation("armaW", "../assets/images/pack/Characters/deathanimations.png", sf::seconds(1), true);
		animW.AddFrames(sf::Vector2i(0, Tile_Size), sf::Vector2i(Tile_Size, Tile_Size), 1);
		weap->GetAnimations().push_back(animW);


		animpg->SwitchAnimation("armaS");
	}
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
	Equipaggiamento equip = Equipaggiamento("weapon", "../assets/images/pack/Weapons/weaponicon.png", "../assets/images/pack/Weapons/weaponiconactivate.png");
	AggiungiOggetto(equip,20);

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
	for (int i = 0; i < equip.size(); ++i) {
		auto spriteIcon = equip[i]->getIconSprite();
		spriteIcon.setPosition(RecognizePositionSlotById(i));
		context.wind->Draw(spriteIcon);
	}
	
	
}
void Inventario::DrawItems() {
	for (auto i : equip) {
		if (i == nullptr)
			continue;

		if(i->GetUsing())
			if (static_cast<Arma*>(i) == nullptr) {
				//armatura
			}
			else {
				context.wind->Draw(((Arma*)i)->GetSprite());
			}
		}
}
	
void Inventario::UpdateItems(sf::Time const& dt) {
	
	Giocatore* giocatore = context.entityManager->GetGiocatore();
	for (auto i : equip) {
		if (i == nullptr)
			continue;

		auto ps = static_cast<Arma*>(i);
		if ( ps == nullptr) {
			//armatura
		}
		else {
			

			float widthWeap = ((Arma*)i)->GetSprite().getGlobalBounds().width;
			float heightWeap = ((Arma*)i)->GetSprite().getGlobalBounds().height;
			float playerWidth = giocatore->GetSprite().getGlobalBounds().width;
			float playerHeight = giocatore->GetSprite().getGlobalBounds().height;
			char direction = giocatore->GetLastDirection();

			((Arma*)i)->GetAnimpg()->update(dt);
			
		}
		//se inventario è visibile
		if (isVisible) {
			animpg.update(dt);
			animpgMoneta.update(dt);
		}
		
	}
}

void Inventario::setContext(SharedContext& context) {
	this->context = context;
}

bool Inventario::isInventoryVisibile() const
{
	return isVisible;
}

void Inventario::ToggleVisibility()
{
	isVisible = !(isVisible); //setta l'inventario visibile
	sf::sleep(sf::seconds(0.1f));
}

void Inventario::AddDenaro(unsigned int den)
{
	denaro += den;

	if(den > 0)
		std::cout << "Hai guadagnato " << den << " denari" << std::endl;
}

void Inventario::DecreaseDenaro(unsigned int den)
{
	denaro -= den;
}

int Inventario::GetDenaro() const
{
	return denaro;
}

bool Inventario::InterazioneSlot() {
	sf::Mouse mouse = sf::Mouse();
	
	int posX = floor(((mouse.getPosition().x - context.wind->GetRenderWindow()->getPosition().x) / 32)); // bordo sinistro schermo  - bordo sinistro finestra 
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
	if (interazioneSlot.getElapsedTime().asSeconds() < tempoMax)
		return false;
	if (slot.size() < Hashcode + 1) {
		//caso di uscita nello slot che premo non c'è nulla
		// in generale quindi l'inventario (vettore di slot) è sortato
		
	}
	if (Hashcode < 0)
		return false;
	if (Hashcode >= equip.size())
		return false;

	if (idActiveWeapon != Hashcode) {
		if(idActiveWeapon!=-1)
			equip[idActiveWeapon]->ToggleIcon();

		idActiveWeapon = Hashcode;
	}

	equip[Hashcode]->ToggleIcon();
	if (!equip[Hashcode]->GetUsing()) {
		idActiveWeapon = -1;
	}


	interazioneSlot.restart();
	return true;
}

sf::Vector2f Inventario::RecognizePositionSlotById(int id) {
	int diffx, diffy;

	diffx = context.wind->GetViewSpace().left + ((int)((id)%4))*32 +3*32+5+(id%4)*8.5 +32, 
	diffy = context.wind->GetViewSpace().top + (context.wind->GetViewSpace().height) - 32*6 -5 +(id/4)*32 + (id /4) * 8.5;

	//std::cout << "id: " << id << " diff: " << diffx << " " << diffy << std::endl;

	return sf::Vector2f(diffx , diffy);
}