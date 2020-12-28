
#pragma once
#include <vector>
#include "Arma.h"
#include "SharedContext.h"

class Inventario {
private:
	
	std::vector<Equipaggiamento> equip;
	std::vector<int> slot;

	SharedContext& context;
	Arma arma;
	bool isVisible;
	sf::Text invetoryMenutitle;
	sf::Sprite sprite;
	Animator animpg;
	std::vector<AnimSet> animations;

	sf::Sprite moneta;
	Animator animpgMoneta;
	std::vector<AnimSet> animationsMoneta;
	
	sf::Text denaroText;
	int denaro;

public:
	Inventario(SharedContext& context): context(context), arma("coltello",1,context),isVisible(false), invetoryMenutitle(sf::Text("Inventory", context.assetManager->GetFont("arial.ttf"))), denaroText(sf::Text("", context.assetManager->GetFont("arial.ttf"))),animpg(sprite),animpgMoneta(moneta),denaro(0) {}
	void ConfiguraEquip();
	bool EliminaOggetto(Equipaggiamento const& obj);
	bool AggiungiOggetto(Equipaggiamento const& obj);
	Arma* GetWeapon() {
		return &arma;
	}
	void DrawInventory();
	void DrawItems();
	void UpdateItems(sf::Time const& dt);
	void setContext(SharedContext& context);
	bool isInventoryVisibile();
	void ToggleVisibility();
	void AddDenaro(int den);
	void DecreaseDenaro(int den);
	int GetDenaro();
	bool InterazioneSlot();
};