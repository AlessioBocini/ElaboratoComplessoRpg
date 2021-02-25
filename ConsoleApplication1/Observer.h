#pragma once
#include <string>
#include "SharedContext.h"
class Subject;

class IObserver {
public:
	virtual ~IObserver() {}
	virtual void Update(const std::string& message_from_subject) = 0;
};


class Observer: public IObserver {
public:
	Observer(Subject& sub, SharedContext& context);
	~Observer() override {}
	void Update(const std::string& message_from_subject) override;
private:
	std::string message_from_subject_;
	Subject& subject_;
	SharedContext& context;
	sf::Text text;
};
