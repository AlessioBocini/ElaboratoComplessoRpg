#include "Subject.h"
#include "Observer.h"

void Subject::Attach(Observer* o) {
	_observers.push_back(o);
}
void Subject::Detach(Observer* o) {
	_observers.remove(o);
}
void Subject::Notify() {
	std::list<Observer*>::iterator i;
	for (i = _observers.begin(); i != _observers.end(); i++) {
		(*i)->Update(message_);
	}
}
void Subject::CreateMessage(std::string message) {
	this->message_ = message;
	Notify();
}