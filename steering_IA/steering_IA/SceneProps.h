#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "MainButton.h"

using std::vector;
using std::string;
using sf::RenderWindow;

class SceneProps
{
public:
	vector<MainButton*> m_buttonList;
	virtual void init();
	virtual void update();
	virtual void render(RenderWindow& wnd);
	virtual void destroy();

	virtual void onMouseClick(int x, int y, short btn);
	SceneProps();
	~SceneProps();
};

