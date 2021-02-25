#include "NPC.h"
#include "Giocatore.h"

void Npc::setTypeOfNpc(const int& type) {
	this->typeofNpc = type;
}

bool Npc::Interazione(Entita& ent)
{

	if (clockInterazione.getElapsedTime().asSeconds() < cooldownInterazione) {
		return false;
	}
	ent.GetInventario()->GetDenaro();

	if ((int(NpcType::Shopkeeper)) != this->typeofNpc) {
		return false;
	}

	int costo = 2;
	auto inv = ent.GetInventario();
	if (inv->GetDenaro() >= costo) {
		inv->DecreaseDenaro(costo);
		Equipaggiamento eq = Equipaggiamento("Destroyer", "assets/images/pack/Weapons/weaponicon.png", "assets/images/pack/Weapons/weaponiconactivate.png");
		inv->AggiungiOggetto(eq,50);
		std::cout << "Hai speso " << costo << " denari, hai acquistato " << eq.GetNomeEquip() << std::endl;
	}
	clockInterazione.restart();
	return true;
}

int Npc::getTypeOfNpc() const{
	return this->typeofNpc;
}

bool Npc::Attacco(Entita*ent,int isSkill) {
	return 0;
}
void Npc::Movimento(const float &x, const float &y) {

}