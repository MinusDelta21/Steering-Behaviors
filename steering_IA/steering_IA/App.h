#pragma once
#include "Window.h"
#include "MainMenu.h"
#include <vector>
#include <SFML\Graphics.hpp>
#include "StateMachine.h"
using std::vector;
using sf::RenderWindow;
using sf::Event;
using sf::Mouse;
class StateMachine;
class Window;
class Application
{
	Window m_applicationWnd;
	StateMachine m_FSM;
	bool onInput(Event& _event);
public:
	void initialize();
	void update();
	void render();
	void destroy();
	int run();
	Application();
	~Application();
};

