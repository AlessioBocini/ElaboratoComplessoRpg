#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
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
	sf::RenderWindow* GetRenderWindow();
	void ToggleFullscreen();
	void ToggleFullscreen(EventDetails* details);
	void Close(EventDetails* details = nullptr);
	void Draw(sf::Drawable& drawable);
	sf::FloatRect GetViewSpace(); // funzione che ritorna lo spazio visibile nella mappa.
private:
	bool isfullscreen;
	bool isdone;
	bool isfocused;
	EventManager eventManager;
	std::string windowTitle;
	sf::RenderWindow window;
	sf::Vector2u windowSize;
	void Create();
	void Destroy();
	void Setup(const std::string title, const sf::Vector2u& size, bool fullscreen);
};