#include "stdafx.h"
#include "GameObject.h"

void GameObject::initialize() {

}
void GameObject::update() {

}
void GameObject::render(sf::RenderWindow &wnd) {

}
void GameObject::destroy() {

}

void GameObject::setPosition(unsigned short x, unsigned short y)
{
	m_position.x = x;
	m_position.y = y;
}

void GameObject::setLayer(int layer)
{
	m_layer = layer;

}

GameObject::GameObject()
{
	m_layer = 0;
	m_toDelete = false;
	m_isEnable = true;
}


GameObject::~GameObject()
{
}