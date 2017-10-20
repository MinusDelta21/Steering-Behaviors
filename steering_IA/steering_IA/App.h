#pragma once
#include "Window.h"
#include "MainMenu.h"
#include <vector>
#include <SFML\Graphics.hpp>
using std::vector;
using sf::RenderWindow;
using sf::Event;
using sf::Mouse;
class Application
{
	Window m_applicationWnd;
	vector<Window*>m_windows;
	Window * m_activeWindow;
	bool onInput(Event& _event);
public:
	void initialize();
	void update();
	void render(RenderWindow&window);
	void destroy();
	int run();
	void setWindow(unsigned short index);
	Application();
	~Application();
};

