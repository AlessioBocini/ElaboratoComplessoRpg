#include "AchievementManager.h"
#include "GameManager.h"
void AchievementManager::DisplayAchievement(unsigned int id)
{
	auto& achievement = achievements[id].first;
	if (achievement.isProvided())
		return;

	context.entityManager->GetGiocatore()->GetSubject().CreateMessage(achievement.GetMessage());
	// Print on screen
	

	achievement.SetProvided(true);
}

AchievementManager::AchievementManager(SharedContext& context) :context(context)
{
	AddCombactAchievement("Skeleton Starter",3);
	AddCombactAchievement("Skeleton Killer",10);
}

void AchievementManager::CheckAchievements()
{
	bool condition = false;
	for (int i = 0; i < achievements.size(); ++i) {
		auto ps = dynamic_cast<CombactAchievementTrigger*>(achievements[i].second.get());

		if(ps != nullptr)
		 condition = ps->CheckCondition();

		if (condition)
			DisplayAchievement(i);
		
	}
}

void AchievementManager::AddCombactAchievement(std::string message,unsigned int num, EnemyType enem  )
{
	Achievement ac = Achievement(message);
	achievements.push_back(std::make_pair(ac, std::unique_ptr<AchievementTrigger>(new CombactAchievementTrigger(context, num, enem))));
}
