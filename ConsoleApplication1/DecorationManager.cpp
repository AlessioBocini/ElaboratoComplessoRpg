#include "DecorationManager.h"
#include "GameManager.h"
DecorationManager::DecorationManager(SharedContext* context) : context(context){}
DecorationManager::~DecorationManager()
{
	for (auto i : deco) {
		delete i;
	}
	deco.clear();
}

int DecorationManager::AddArredamento(const std::string& name, const std::string& filepath, const sf::Vector2f &pos) {
	Arredamento* arredamento = new Arredamento(name, filepath, pos);
	int frameX = 0, frameY = 0, numframes = 0;
	sf::Vector2i spritesize = context->gameManager->GetSpriteSize();
	std::string path = "assets/images/pack/Characters/people1.png";

	if (name == "laghetto") {
		path = "assets/images/pack/Tilesets/AH_A1.png";
		numframes = 1;
	}
	else if (name == "lago grande") {
		path = "assets/images/pack/Tilesets/AH_A1.png";
		numframes = 3;
		frameY = spritesize.y;
		spritesize *= 2;
	}
	else if (name == "porta") {
		path = "assets/images/pack/Characters/!AH-Objects.png";
		frameX = spritesize.x * 3;
		numframes = 4;
		auto& anim1 = arredamento->GetAnimpg()->CreateAnimation("animation1", path, sf::seconds(1), true);
		anim1.AddFrames(sf::Vector2i(frameX, frameY), spritesize, numframes,true);
		arredamento->GetAnimations().push_back(anim1);
		numframes = 1;
	}
	else if (name == "casa") {
		path = "assets/images/house.png";
		numframes = 1;
		spritesize *= 3;
	}
	else if (name == "sedia >") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		frameY = spritesize.y * 3;
		frameX = spritesize.x * 2;
		numframes = 1;
	}
	else if (name == "sedia <") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		frameY = spritesize.y * 3;
		frameX = spritesize.x;
		numframes = 1;
	}
	else if (name == "tavolino") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		frameY = spritesize.y * 3;
		numframes = 1;
	}
	else if (name == "scrivania") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		numframes = 1;
		frameY = spritesize.y * 11;
		frameX = spritesize.x;
		spritesize.x *= 3;

	}
	else if (name == "letto orizzontale") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		numframes = 1;
		frameY = spritesize.y * 4;
		spritesize.x *= 2;
	}
	else if (name == "letto verticale") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		numframes = 1;
		frameY = spritesize.y * 5;
		spritesize.y *= 2;
	}
	else if (name == "scrivania verticale") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		numframes = 1;
		frameY = spritesize.y * 9;
		spritesize.y *= 3;
	}
	else if (name == "fiori") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		numframes = 1;
		frameY = spritesize.y * 2;
	}
	else if (name == "erba") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		numframes = 1;
		frameX = spritesize.x * 6;
	}
	else if (name == "roccia grande") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		numframes = 1;
		frameX = spritesize.x * 7;
		frameY = spritesize.y;
	}
	else if (name == "ciottoli") {
		path = "assets/images/pack/Tilesets/AH_B.png";
		numframes = 1;
		frameX = spritesize.x * 6;
		frameY = spritesize.y;
	}
	auto& anim = arredamento->GetAnimpg()->CreateAnimation("animation", path, sf::seconds(1), true);
	anim.AddFrames(sf::Vector2i(frameX, frameY), spritesize, numframes);
	arredamento->GetAnimations().push_back(anim);
	arredamento->GetSprite().setPosition(pos.x * 32, pos.y * 32);
	arredamento->GetAnimpg()->SwitchAnimation("animation");
	deco.push_back(arredamento);
	return 0;

}

std::vector<Arredamento*> DecorationManager::GetDecorations() const
{
	return deco;
}

Arredamento* DecorationManager::GetArredamentoByCoords(int x, int y) const
{
	Arredamento* result = nullptr;

	for (Arredamento* it : deco) {
		int DecoPosX = floor(it->GetSprite().getPosition().x / Sheet::Tile_Size),
			DecoPosY = floor(it->GetSprite().getPosition().y / Sheet::Tile_Size);

		if (DecoPosX == x && DecoPosY == y) {
			result = it;
			break;
		}
	}
	return result;
}

void DecorationManager::Update(const sf::Time& dt)
{
			for (auto i : deco) {
				Animator* animpg = i->GetAnimpg();
				if (i->GetName() == "porta") {
					if (animpg->GetCurrentFrame() == 3) {
				
						animpg->SwitchAnimation("animation");
						i->Teleport(context);//teleport
						
					}
				}

				animpg->update(dt);

			}
}

void DecorationManager::Draw()
{
	for (auto i : deco)
		context->wind->Draw(i->GetSprite());
}
/*bool DecorationManager::GetTrascendent()
{
	return this->isTrascendent;
}

void DecorationManager::SetTrascendent(bool trascendence)
{
	this->isTrascendent = trascendence;
}*/
