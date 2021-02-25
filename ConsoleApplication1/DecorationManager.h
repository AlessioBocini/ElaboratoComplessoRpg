#pragma once
#include <string>
#include <SFML\System\Vector2.hpp>
#include <vector>
#include "Arredamento.h"
class DecorationManager {
public:
	DecorationManager(SharedContext* context);
	~DecorationManager();
	int AddArredamento(const std::string& name, const std::string& filepath, const sf::Vector2f &pos); 
	std::vector<Arredamento*> GetDecorations() const;
	Arredamento* GetArredamentoByCoords(int x, int y) const;
	void Update(const sf::Time& dt);
	void Draw();
private:
	std::vector<Arredamento*> deco;
	SharedContext* context;
};