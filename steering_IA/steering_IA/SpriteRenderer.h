#pragma once
#include "GameObject.h"
#include <SFML\Graphics.hpp>
#include "Vector3.h"
#include <string>
using sf::Sprite;
using sf::Texture;
using sf::RenderWindow;
using sf::Color;
using std::string;
class SpriteRenderer :
	public GameObject
{
protected:
	Sprite m_sprite;
	Texture m_texture;
public:
	bool m_visible;
	virtual void init();
	virtual void render(RenderWindow& wnd);
	virtual void update();
	virtual void destroy();
	void setSprite(string path);
	void setColor(Vector3 Color, float Alpha);
	void setScale(float Scale);
	SpriteRenderer();
	~SpriteRenderer();
};

