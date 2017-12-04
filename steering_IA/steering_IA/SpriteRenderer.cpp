#include "stdafx.h"
#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer()
{
}


SpriteRenderer::~SpriteRenderer()
{
	destroy();
}

void SpriteRenderer::init()
{
	m_texture.loadFromFile("Sprites/orange-circle-md.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setColor(Color::White);

	sf::FloatRect rect = m_sprite.getLocalBounds();
	m_sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);
}

void SpriteRenderer::render(RenderWindow & wnd)
{
	RenderWindow* ptrWin = &wnd;
	if (m_visible)
	{
		wnd.draw(m_sprite);
	}
}

void SpriteRenderer::update()
{
	m_sprite.setPosition(m_position.x, m_position.y);
}

void SpriteRenderer::destroy()
{
}

void SpriteRenderer::setSprite(string path)
{
	if (!m_texture.loadFromFile(path)) m_texture.loadFromFile("Sprites/orange-circle-md.png");
	m_sprite.setTexture(m_texture, true);
	sf::FloatRect rect = m_sprite.getLocalBounds();
	m_sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);
}

void SpriteRenderer::setColor(Vector3 Color, float Alpha)
{
	m_sprite.setColor(sf::Color(Color.x, Color.y, Color.z, Alpha));
}

void SpriteRenderer::setScale(float Scale)
{
	m_sprite.scale(Scale, Scale);
}
