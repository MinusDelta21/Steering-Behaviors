#include "stdafx.h"
#include "App.h"



void Application::initialize() {
	m_applicationWnd.initialize(1200, 720, "MainWindow");
	
	MainMenu* Lobby = new MainMenu();
	Lobby->initialize();
	m_windows.push_back(Lobby);
	setWindow(0);
}
void Application::update() {
	m_applicationWnd.update();
	m_activeWindow->update();
}
void Application::render(RenderWindow&window) {
	m_applicationWnd.clear();
	m_activeWindow->render(m_applicationWnd.m_window);
	m_applicationWnd.render(m_applicationWnd.m_window);
}
void Application::destroy() {
	m_applicationWnd.destroy();
	for (unsigned int i = 0; i < m_windows.size(); ++i)
		m_windows[i]->destroy();
}
int Application::run()
{
	sf::Event event;

	while (onInput(event)) {
		update();
		render(m_applicationWnd.m_window);
	}

	destroy();
	return 0;
}
void Application::setWindow(unsigned short index)
{
	if (index >= m_windows.size())
		return;
	if (m_activeWindow != NULL)
		m_activeWindow->destroy();
	m_activeWindow = m_windows[index];
	m_activeWindow->initialize(m_applicationWnd.m_winSize[0],m_applicationWnd.m_winSize[1],m_applicationWnd.m_winName);
}

bool Application::onInput(Event & _event)
{
	while (m_applicationWnd.m_window.pollEvent(_event)) {
		switch (_event.type) {
		case Event::Closed:
			destroy();
			return false;
			break;
		case Event::MouseButtonPressed:
			if (Mouse::isButtonPressed(sf::Mouse::Left))
				m_activeWindow->onMouseClick(Mouse::getPosition(m_applicationWnd.m_window).x, Mouse::getPosition(m_applicationWnd.m_window).y, 0);
			break;
		default:
			return true;
		}
	}
	return true;
}

Application::Application()
{
}


Application::~Application()
{
}
