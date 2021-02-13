
#pragma once
#include <vector>
#include "Arma.h"
#include "SharedContext.h"

class Inventario {
private:
	
	std::vector<Equipaggiamento*> equip;
	std::vector<int> slot;

	SharedContext& context;
	bool isVisible;
	sf::Text invetoryMenutitle;
	sf::Sprite sprite;
	Animator animpg;
	std::vector<AnimSet> animations;

	sf::Sprite moneta;
	Animator animpgMoneta;
	std::vector<AnimSet> animationsMoneta;
	
	sf::Clock interazioneSlot;
	float tempoMax = 0.2;
	sf::Text denaroText;
	unsigned int denaro;
	unsigned int idActiveWeapon = -1;
public:
	Inventario(SharedContext& context): context(context),isVisible(false), invetoryMenutitle(sf::Text("Inventory", context.assetManager->GetFont("arial.ttf"))), denaroText(sf::Text("", context.assetManager->GetFont("arial.ttf"))),animpg(sprite),animpgMoneta(moneta),denaro(0) {}
	void ConfiguraEquip();
	bool EliminaOggetto(Equipaggiamento& obj);
	bool AggiungiOggetto(Equipaggiamento& obj, int value);
	Arma* GetWeapon() {
		if (idActiveWeapon == -1) return nullptr;
		return static_cast<Arma*>(equip[idActiveWeapon]);
	}
	void DrawInventory();
	void DrawItems();
	void UpdateItems(sf::Time const& dt);
	void setContext(SharedContext& context);
	bool isInventoryVisibile() const;
	void ToggleVisibility();
	void AddDenaro(unsigned int den);
	void DecreaseDenaro(unsigned int den);
	int GetDenaro() const;
	bool InterazioneSlot();
	int RecognizeSlot();
	sf::Vector2f RecognizePositionSlotById(int id);
};