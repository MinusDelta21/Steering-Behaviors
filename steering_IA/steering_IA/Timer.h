#pragma once
#include "SFML\System\Clock.hpp"
#include "SFML\System\Time.hpp"

using sf::Time;
using sf::Clock;

class Timer
{
	Clock		m_clock;
	Time		m_frameTime;
public:
	void		init();
	void		update();
	void		destroy();
	float		getFrameTime();
	Timer();
	~Timer();
};

