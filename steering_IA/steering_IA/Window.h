#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Timer.h"
#include "State.h"
#include "App.h"
using std::string;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Color;
using sf::Event;
using sf::Clock;
using sf::Time;
class Application;
class Timer;
class State;

class Window: public State
{
protected:
public:
	Application* m_app;
	RenderWindow m_window;
	unsigned short m_winSize[2];
	string m_winName;
	Timer m_wndTime;
	bool pollEvent(Event& _event);
	virtual void initialize(unsigned short x,unsigned short y, string winName);
	virtual void update();
	virtual void render();
	virtual void clear();
	virtual void destroy();
	Window(unsigned int id, const std::string& name, Application* app) : State(id), m_winName(name), m_app(app) {}
	virtual ~Window();
};

