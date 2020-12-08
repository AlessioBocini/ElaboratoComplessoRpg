#include "NPC.h"

void Npc::setMap(const std::string& map) {
	this->map = map;
}
void Npc::setTypeOfNpc(const int& type) {
	this->typeofNpc = type;
}
std::string Npc::getMap() {
	return this->map;
}
int Npc::getTypeOfNpc() {
	return this->typeofNpc;
}

void Npc::Attacco(bool isSkill) {
}
void Npc::Movimento(float x, float y) {

}