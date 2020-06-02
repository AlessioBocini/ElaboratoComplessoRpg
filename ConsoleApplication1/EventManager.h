#pragma once
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <functional>
#include <vector>

enum class EventType {
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count +1, Mouse , Joystick

};

struct EventInfo {
	EventInfo() { code = 0; }
	EventInfo(int cevent) : code(cevent){}
	union {	
		// uso una union perché magari in futuro potrebbe servirmi conoscere altre informazioni sugli eventi
		// non solo il codice.
		int code;
	};
};


// definisco un nuovo tipo che fa il binding dell'evento con le sue info
using Events = std::vector<std::pair<EventType, EventInfo>>;


struct EventDetails {
	EventDetails(const std::string& bindName) : name(bindName) {
		clear();
	}
	std::string name;

	sf::Vector2i size;
	sf::Uint32 textEntered;
	sf::Vector2i mouse;
	int mouseWheelDelta;
	int keyCode; //key code singolo.

	void clear() {
		size = sf::Vector2i(0, 0);
		textEntered = 0;
		mouse = sf::Vector2i(0, 0);
		keyCode = -1;
		mouseWheelDelta = 0;
	}
};


struct Binding {
	Binding(const std::string& name): name(name), details(name), cEvents(0){}
	~Binding() {}
	void BindEvent(EventType type, EventInfo info = EventInfo()) {
		events.emplace_back(type, info);
	}
	Events events;
	std::string name;
	int cEvents; // counter degli eventi che stanno accadendo in contemporanea
	EventDetails details;
};

using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;
using Bindings = std::unordered_map<std::string, Binding*>;	// è un container associativo, ci sarà solo un binding per azione.



class EventManager {
public:
	EventManager();
	~EventManager();

	bool AddBinding(Binding* binding);
	bool RemoveBinding(std::string name);
	void SetFocus(const bool& focus);

	template<class T>
	bool AddCallback(StateType l_state, const std::string& l_name,
		void(T::* l_func)(EventDetails*), T* l_instance)
	{
		auto itr = callbacks.emplace(l_state, CallbackContainer()).first;
		auto temp = std::bind(l_func, l_instance, std::placeholders::_1);
		return itr->second.emplace(l_name, temp).second;
	}

	bool RemoveCallback(StateType l_state, const std::string& l_name) {
		auto itr = callbacks.find(l_state);
		if (itr == callbacks.end()) { return false; }
		auto itr2 = itr->second.find(l_name);
		if (itr2 == itr->second.end()) { return false; }
		itr->second.erase(l_name);
		return true;
	}
	void SetCurrentState(StateType l_state);
	void HandleEvent(sf::Event& event);
	void Update();
	sf::Vector2i GetMousePos(sf::RenderWindow* wind = nullptr) {
		return (wind ? sf::Mouse::getPosition(*wind) : sf::Mouse::getPosition());
	}
private:
	void LoadBindings();
	Bindings bindings;
	Callbacks callbacks;
	bool hasFocus;
	StateType currentState;

};