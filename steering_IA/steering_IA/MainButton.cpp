#include "stdafx.h"
#include "MainButton.h"

void MainButton::init()
{
	if (!m_texture.loadFromFile("btnSprite.png"))
		return;

	m_btnSprite.setTexture(m_texture);
	m_btnSprite.setPosition(m_position.x, m_position.y);
	return;
}

void MainButton::update()
{
	//m_label.setPosition(m_position.x, m_position.y);
	//m_btnSprite.setPosition(m_position.x, m_position.y);
}

void MainButton::render(RenderWindow & wnd)
{
	wnd.draw(m_btnSprite);
}

void MainButton::destroy()
{

}
MainButton::MainButton()
{
}


MainButton::~MainButton()
{
}
