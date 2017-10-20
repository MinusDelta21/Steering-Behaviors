#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using std::string;
using sf::RenderWindow;
using sf::VideoMode;
class Window
{
protected:
public:
	RenderWindow m_window;

	unsigned short m_winSize[2];
	string m_winName;
	void onMouseClick(int x, int y, short button);
	void initialize(unsigned short x,unsigned short y, string winName);
	void update();
	void render(RenderWindow&window);
	void clear();
	void destroy();
	Window();
	~Window();
};

