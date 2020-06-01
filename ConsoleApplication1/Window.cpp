#include "Window.h"
#include "Animator.h"


Window::Window()
{
	Setup("Window", sf::Vector2u(640, 480), false);
}
Window::Window(const std::string title, const sf::Vector2u& size, bool fullscreen) {
	Setup(title, size, fullscreen);
}
Window::~Window() {
	Destroy();
}
void Window::Setup(const std::string title, const sf::Vector2u& size, bool fullscreen) {
	windowTitle = title;
	windowSize = size;
	isFocused = true;
	eventManager.AddCallback("Fullscreen_toggle", &Window::ToggleFullscreen, this);
	eventManager.AddCallback("Window_close", &Window::Close, this);
	isfullscreen = fullscreen;
	isdone = false;
	Create();
}
void Window::Create() {
	auto style = (isfullscreen == true ? sf::Style::Fullscreen : sf::Style::Default);
	window.create({ windowSize.x , windowSize.y, 32 }, windowTitle, style);
}
void Window::Destroy() {
	window.close();
}
void Window::Update() {
	sf::Event ev;
	while (window.pollEvent(ev)) {
		if (ev.type == sf::Event::LostFocus) {
			isFocused = false;
			eventManager.SetFocus(false);
		}
		else if (ev.type == sf::Event::GainedFocus) {
			isFocused = true;
			eventManager.SetFocus(true);
		}
		eventManager.HandleEvent(ev);
	}
	eventManager.Update();
}
void Window::ToggleFullscreen() {
	isfullscreen = !isfullscreen;
	Destroy();
	Create();
}
void Window::BeginDraw() {
	window.clear(sf::Color::Black);
}
void Window::EndDraw() {
	window.display();
}
bool Window::isDone() {
	return this->isdone;
}
bool Window::isFullscreen() {
	return this->isfullscreen;
}
sf::Vector2u Window::GetwindowSize() {
	return windowSize;
}
void Window::Draw(sf::Drawable& drawable) {
	window.draw(drawable);
}

