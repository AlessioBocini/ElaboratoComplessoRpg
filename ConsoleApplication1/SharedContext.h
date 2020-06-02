#pragma once
#include "EventManager.h"
#include "Window.h"
struct SharedContext {
	SharedContext () : wind(nullptr), eventManager(nullptr){}
	Window* wind;
	EventManager* eventManager;
};