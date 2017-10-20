#include "stdafx.h"
#include "Window.h"


void Window::onMouseClick(int x, int y, short button)
{
}

void Window::initialize(unsigned short x, unsigned short y, string winName)
{
	this->m_winSize[0] = x;
	this->m_winSize[1] = y;
	m_winName = winName;
	m_window.create(VideoMode(m_winSize[0], m_winSize[1]), m_winName);
}

void Window::update()
{
}

void Window::render(RenderWindow&window)
{
	m_window.display();
}

void Window::clear()
{
	m_window.clear();
}

void Window::destroy()
{
	m_window.close();
}

Window::Window()
{
}


Window::~Window()
{
}