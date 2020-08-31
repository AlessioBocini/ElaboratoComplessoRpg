#pragma once
#include "EventManager.h"
#include "AssetManager.h"
#include "Window.h"

class Mondo;
class GameManager;
class EntityManager;
// struttura che contiene tutte quelle classi/devices comunemente più utilizzati.
struct SharedContext {
	SharedContext () : wind(nullptr), eventManager(nullptr), gameManager(nullptr),assetManager(nullptr),gameMap(nullptr),entityManager(nullptr){}
	Window* wind;
	EventManager* eventManager;
	GameManager* gameManager;
	AssetManager* assetManager;
	Mondo* gameMap;
	EntityManager* entityManager;

};