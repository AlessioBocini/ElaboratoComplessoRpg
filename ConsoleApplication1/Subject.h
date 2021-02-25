#pragma once
#include <list>
#include <string>

class Observer;

class ISubject {
public:
	virtual ~ISubject() {}
	virtual void Attach(Observer* observer) = 0;
	virtual void Detach(Observer* observer) = 0;
	virtual void Notify() = 0;
};

class Subject : public ISubject {
public:
	~Subject() override {}
	void Attach(Observer* observer) override;
	void Detach(Observer* observer) override;
	void Notify() override;
	virtual void CreateMessage(std::string message = "Empty");
protected:
private:
	std::list<Observer*> _observers;
	std::string message_;
};

