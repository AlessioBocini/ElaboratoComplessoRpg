#include "Quickslot.h"
Quickslot::Quickslot(SharedContext& context, unsigned int id) : context(context),  id(id){}
Quickslot::~Quickslot()
{
}
void Quickslot::Draw()
{
	Icon.setPosition(context.wind->GetViewSpace().left + context.wind->GetViewSpace().width / 3 +32*id, context.wind->GetViewSpace().top + (context.wind->GetViewSpace().height) - 32);
	context.wind->Draw(Icon);
	//display testo TODO
	// id => skill caster

}

void Quickslot::ConfigureQuickslot()
{
	//skill TODO 
	Icon = sf::Sprite(context.assetManager->GetTexture("assets/images/quickslot.png"));
}


