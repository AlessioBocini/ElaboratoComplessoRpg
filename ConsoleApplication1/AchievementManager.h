#pragma once
#include "Achievement.h"
#include <vector>

using achievepair = std::pair<Achievement, std::unique_ptr<AchievementTrigger>>;
class AchievementManager {
public:
	AchievementManager(SharedContext& context);
	~AchievementManager() {
		achievements.clear();
	}

	void CheckAchievements();
	void AddCombactAchievement(std::string message,  unsigned int num = 4 ,EnemyType enem = EnemyType::Skeleton);
private:
	std::vector<achievepair> achievements;
	SharedContext& context;
	void DisplayAchievement(unsigned int id);


};