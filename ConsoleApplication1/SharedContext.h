#pragma once
#include "EventManager.h"
#include "Window.h"

// struttura che contiene tutte quelle classi/devices comunemente pi� utilizzati.
struct SharedContext {
	SharedContext () : wind(nullptr), eventManager(nullptr){}
	Window* wind;
	EventManager* eventManager;

};