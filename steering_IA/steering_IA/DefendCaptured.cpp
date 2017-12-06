#include "stdafx.h"
#include "DefendCaptured.h"
#include "Agent.h"



void DefendCaptured::onEnter()
{
}

unsigned int DefendCaptured::update(void * pObject)
{
	Agent* leader = m_agent->leaderInSight();
	if (leader != nullptr)
	{
		//SEGUIR AL LIDER
		m_agent->addTarget(leader, TARGET::Leader);
	}
	else
	{
		// HE PERDIDO AL LIDER
		m_agent->m_fsm.SetState(BOIDSTATE::Idle);
		return 0;
	}

	if (m_agent->enemyInSight() != nullptr)
	{
		//OH SHIT, UN ENEMIGO TENGO QUE REVENTARLO
		m_agent->m_fsm.SetState(BOIDSTATE::AttackEnemy);
		return 0;
	}
	return 0;
}

void DefendCaptured::onExit()
{
	m_agent->removeTarget(TARGET::Leader);

}


DefendCaptured::~DefendCaptured()
{
}
