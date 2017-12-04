#pragma once
#include "Window.h"
#include <vector>
using std::vector;
class MainMenu: public Window
{
	vector<MainButton*> m_buttonList;
public:
	void initialize();
	void update();
	void render(RenderWindow&wnd);
	void destroy();
	MainMenu();
	~MainMenu();
};
