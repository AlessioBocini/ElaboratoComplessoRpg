#pragma once
#include <string>
#include "SharedContext.h"
#include "Entita.h"
class Achievement {
private:
	std::string message;
	bool provided;
public:
	bool isProvided() const {
		return provided;
	}
	void SetProvided(bool value) {
		provided = value;
	}
	std::string GetMessage() const {
		return message;
	}
	void SetMessage(std::string message) {
		this->message = message;
	}
	Achievement(std::string message) :message(message), provided(false){}
};

class AchievementTrigger {
public:
	virtual bool CheckCondition() = 0;
	virtual ~AchievementTrigger(){}
};

class CombactAchievementTrigger :public AchievementTrigger {
public: 
	bool CheckCondition() override;
	CombactAchievementTrigger(SharedContext& context, unsigned int numbermobs = 4, EnemyType enem = EnemyType::Skeleton): context(context),numbermobs(numbermobs),enemytype(enem){}
	~CombactAchievementTrigger() override {}
private:
	unsigned int numbermobs;
	EnemyType enemytype;
	SharedContext& context;
};


