#include "Observer.h"
#include "Subject.h"
#include "GameManager.h"
#include <iostream>
Observer::Observer(Subject& sub, SharedContext& context) :subject_(sub),context(context),text(sf::Text("", context.assetManager->GetFont("arial.ttf"))) {
	sub.Attach(this);
}

void Observer::Update(const std::string& message_from_subject) {
	message_from_subject_ = message_from_subject;
	context.gameManager->SetTextAchivement(message_from_subject);
	std::cout << "You've got an achievement : "<<message_from_subject << std::endl;
	context.gameManager->SetDisplayAchievement(true);
	context.gameManager->RestartAchievementClock();
}
