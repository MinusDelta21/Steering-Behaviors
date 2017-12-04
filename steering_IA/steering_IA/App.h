#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "StateMachine.h"
using std::vector;
using sf::RenderWindow;
using sf::Event;
using sf::Mouse;
class StateMachine;
class Window;
class GameWindow;
class Application
{
	GameWindow* m_applicationWnd;
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

