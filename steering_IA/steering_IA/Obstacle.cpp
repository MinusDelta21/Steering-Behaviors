#include "stdafx.h"
#include "Obstacle.h"

void Obstacle::initialize() {
	init();
}
void Obstacle::update() {
	m_sprite.setPosition(m_position.x, m_position.y);
	m_collider.setPosition(m_position.x, m_position.y);
}
void Obstacle::render(sf::RenderWindow& wnd) {
	if (m_visible)
		wnd.draw(m_sprite);
}
void Obstacle::setRadius(float radius)
{
	m_radius = radius;
	m_collider.setRadius(radius);
	sf::FloatRect obsRect = m_collider.getLocalBounds();
	m_collider.setOrigin(obsRect.width * 0.5f, obsRect.height * 0.5f);
}
void Obstacle::destroy() {

}
Obstacle::Obstacle()
{
	m_tag = "Obstacle";
	m_radius = 70;
	init();
}


Obstacle::~Obstacle()
{
}
