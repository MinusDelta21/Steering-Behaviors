#include "stdafx.h"
#include "SFMLWindow.h"


void CSFMLWindow::init()
{
}

void CSFMLWindow::update()
{
}

void CSFMLWindow::render()
{
	m_window.display();
}

void CSFMLWindow::clear()
{
	m_window.clear();
}

void CSFMLWindow::destroy()
{
	m_window.close();
}

void CSFMLWindow::initWindow(short _w, short _h, string _title)
{
	this->m_width = _w;
	this->m_height = _h;
	this->m_title = _title;
	m_window.create(VideoMode(_w, _h), _title);
}

CSFMLWindow::CSFMLWindow()
{
}


CSFMLWindow::~CSFMLWindow()
{
}
