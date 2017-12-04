#include "stdafx.h"
#include "Dead.h"



void Dead::onEnter()
{
	m_time = 0;
}

unsigned int Dead::update(void * pObject)
{
	m_agent->m_position = Vector3(-300, -300);
	GameWindow* gmScn = reinterpret_cast<GameWindow*>(pObject);
	m_time += gmScn->m_time.getFrameTime();

	if (m_agent->m_isEnable)
	{
		m_agent->m_isEnable = false;
	}


	if (m_agent->flagPower()) {
		vector<Flag*> flags = gmScn->getObjs<Flag>();

		for (int i = 0; i < flags.size(); ++i)
		{
			if (flags[i]->m_team != m_agent->m_team)
			{
				if (!flags[i]->isEnable())
				{
					flags[i]->setEnable(true);
					break;
				}
			}
		}
		m_agent->setFlagPower(false);
	}

	if (m_time >= m_respawnTime)
	{
		m_agent->m_position = m_agent->m_respawnPosition;
		m_agent->m_fsm.SetState(BOIDSTATE::Idle);
		return 0;
	}
	return 0;
}

void Dead::onExit()
{
}

Dead::~Dead()
{
}
