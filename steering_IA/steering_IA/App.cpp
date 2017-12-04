#include "stdafx.h"
#include "App.h"
#include "GameWindow.h"
#include "Window.h"



void Application::initialize() {
	m_applicationWnd = new GameWindow(0, "Capture The Flag II", this);
	m_applicationWnd->init();
}
void Application::update() {
	m_applicationWnd->update(nullptr);
}
void Application::render() {
	m_applicationWnd->render();
	m_applicationWnd->clear();
}
void Application::destroy() {
	m_applicationWnd->destroy();
}
int Application::run()
{
	sf::Event event;

	while (onInput(event)) {
		update();
		render();
	}

	destroy();
	return 0;
}

bool Application::onInput(Event & _event)
{
	while (m_applicationWnd->pollEvent(_event)) {
		switch (_event.type) {
		case Event::Closed:
			destroy();
			return false;
			break;
		default: {

		}
				 return true;
		}
	}
	m_FSM.UpdateState(reinterpret_cast<void*>(&_event));
	return true;
}

Application::Application()
{
	
}


Application::~Application()
{
}
