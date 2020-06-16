#include "EventManager.h"
#include <iostream>

EventManager::EventManager() :hasFocus(true) {
	LoadBindings();
}
EventManager::~EventManager() {
	for (auto& it : bindings) {
		delete it.second;
		it.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding* binding) {
	if (bindings.find(binding->name) != bindings.end()) {
		return false;
	}
	return bindings.emplace(binding->name, binding).second;
}
bool EventManager::RemoveBinding(std::string name) {
	auto it = bindings.find(name);
	if (it == bindings.end()) 
		return false;

	delete it->second;
	bindings.erase(it);

	return true;
}
void EventManager::SetFocus(const bool& l_focus) { 
	hasFocus = l_focus; 
}

void EventManager::SetCurrentState(StateType l_state) {
	currentState = l_state;
}

void EventManager::HandleEvent(sf::Event& event) {
	for (auto& itr : bindings) {
		Binding* bind = itr.second;
		for (auto& it : bind->events) {
			EventType sfmlEvent = (EventType)event.type;
			if (it.first != sfmlEvent) continue;
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {
				if (it.second.code == event.key.code) {
					//match degli eventi e incremento del counter
					if (bind->details.keyCode != -1)
						bind->details.keyCode = it.second.code;
					++(bind->cEvents);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) {
				if (it.second.code == event.mouseButton.button) {
					//match degli eventi e incremento del counter
					bind->details.mouse.x = event.mouseButton.x;
					bind->details.mouse.y = event.mouseButton.y;
					if (bind->details.keyCode != -1) {
						bind->details.keyCode = it.second.code;
					}
					++(bind->cEvents);
					break;
				}
			}
			else {
				if (sfmlEvent == EventType::MouseWheel) {
					bind->details.mouseWheelDelta = event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					bind->details.size.x = event.size.width;
					bind->details.size.y = event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					bind->details.textEntered = event.text.unicode;
				}
				++(bind->cEvents);
			}
		}
	}
}

void EventManager::Update() {
	if (!hasFocus) {
		return;
	}
	for (auto& itr : bindings) {
		Binding* bind = itr.second;
		for (auto& it : bind->events) {
			switch (it.first)
			{
			case (EventType::Keyboard) :
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(it.second.code))) {
					if (bind->details.keyCode != -1) {
						bind->details.keyCode = it.second.code;
					}
					++(bind->cEvents);
				}
					break;
			case (EventType::Mouse):
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(it.second.code))) {
					if (bind->details.keyCode != -1) {
						bind->details.keyCode = it.second.code;
					}
					++(bind->cEvents);
				}
				break;
			}
		}
		if (bind->events.size() == bind->cEvents) {
			auto statecallbacks = callbacks.find(currentState);
			auto othercallbacks = callbacks.find(StateType(0));

			if (statecallbacks != callbacks.end()) {
				auto callitr = statecallbacks->second.find(bind->name);
				if (callitr != statecallbacks->second.end()) {
					callitr->second(&bind->details);	// implemento il wrapper della funzione passando details
				}
			}
			if (othercallbacks != callbacks.end()) {
				auto callitr = othercallbacks->second.find(bind->name);
				if (callitr != othercallbacks->second.end()) {
					callitr->second(&bind->details); // implemento il wrapper della funzione passando details
				}
			}
		}
		bind->cEvents = 0;
		bind->details.clear();
	}
}
void EventManager::LoadBindings(){
	std::string delimiter = ":";

	std::ifstream _bindings;
	_bindings.open("keys.cfg");
	if (!_bindings.is_open()) { std::cout << "! Failed loading keys.cfg." << std::endl; return; }
	std::string line;
	while (std::getline(_bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) { delete bind; bind = nullptr; break; }
			EventType type = EventType(stoi(keyval.substr(start, end - start)));
			int code = stoi(keyval.substr(end + delimiter.length(),
				keyval.find(delimiter, end + delimiter.length())));

			EventInfo eventInfo;
			eventInfo.code = code;
			bind->BindEvent(type, eventInfo);
		}

		if (!AddBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	_bindings.close();


}