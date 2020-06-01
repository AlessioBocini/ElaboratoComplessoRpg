#pragma once
#include <string>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include "EventManager.h"


class Window {
public:
	Window();
	~Window();
	Window(const std::string title, const sf::Vector2u& size, bool fullscreen);
	void BeginDraw();
	void EndDraw();

	void Update();

	bool isDone();
	bool isFullscreen();
	bool isFocused();
	
	EventManager* GetEventManager();
	sf::Vector2u GetwindowSize();
	void ToggleFullscreen();
	void ToggleFullscreen(EventDetails* details);
	void Close(EventDetails* details = nullptr);
	void Draw(sf::Drawable& drawable);
private:
	bool isfullscreen;
	bool isdone;
	bool isFocused;
	EventManager eventManager;
	std::string windowTitle;
	sf::RenderWindow window;
	sf::Vector2u windowSize;
	void Create();
	void Destroy();
	void Setup(const std::string title, const sf::Vector2u& size, bool fullscreen);
};