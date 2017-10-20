#pragma once
#include "GameObject.h"
using sf::RenderWindow;
using sf::Texture;
using sf::Text;
using sf::Font;
using sf::Sprite;
using sf::Color;
class MainButton : public GameObject
{
	Texture	m_texture;
	Sprite m_btnSprite;
	unsigned short m_width;
	unsigned short m_height;
public:
	void init();
	void update();
	void render(RenderWindow& wnd);
	void destroy();
	MainButton();
	~MainButton();
};

