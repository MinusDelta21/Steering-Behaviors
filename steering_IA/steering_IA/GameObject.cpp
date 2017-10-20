#include "stdafx.h"
#include "GameObject.h"

void GameObject::initialize() {

}
void GameObject::update() {

}
void GameObject::render() {

}
void GameObject::destroy() {

}

void GameObject::setPosition(unsigned short x, unsigned short y)
{
	m_position.x = x;
	m_position.y = y;
}

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}