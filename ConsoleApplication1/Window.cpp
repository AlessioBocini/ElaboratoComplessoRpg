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
sf::FloatRect Window::GetViewSpace() {
	sf::Vector2f viewCenter(window.getView().getCenter()); // prendo il centro della finestra in coords
	sf::Vector2f viewSize(window.getView().getSize()); // prendo lo spazio totale della finestra in coords
	sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2); // prendo la meta della finestra in coords
	sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize); // definisco il rettangolo visibile come centro-metà per largezza e size normale per altezza
	return viewSpace;
}
void Window::Setup(const std::string title, const sf::Vector2u& size, bool fullscreen) {
	windowTitle = title;
	windowSize = size;
	isfocused = true;
	eventManager.AddCallback(StateType(0), "Fullscreen_toggle", &Window::ToggleFullscreen, this);
	eventManager.AddCallback(StateType(0), "Window_close", &Window::Close, this);
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
			isfocused = false;
			eventManager.SetFocus(false);
		}
		else if (ev.type == sf::Event::GainedFocus) {
			isfocused = true;
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

bool Window::isFocused() { 
	return isfocused; 
}
void Window::ToggleFullscreen(EventDetails* l_details) {
	isfullscreen = !isfullscreen;
	window.close();
	Create();
}
void Window::Close(EventDetails* l_details) { 
	isdone = true; 
}
sf::RenderWindow* Window::GetRenderWindow() { return &window; }
EventManager* Window::GetEventManager() { return &eventManager; }