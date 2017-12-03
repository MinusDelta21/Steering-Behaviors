#include "stdafx.h"
#include "Timer.h"


void Timer::init()
{
	m_clock.restart();
}

void Timer::update()
{
	m_frameTime = m_clock.restart();
}

void Timer::destroy()
{
}

float Timer::getFrameTime()
{
	return m_frameTime.asSeconds();
}

Timer::Timer()
{
	init();
}


Timer::~Timer()
{
	destroy();
}
