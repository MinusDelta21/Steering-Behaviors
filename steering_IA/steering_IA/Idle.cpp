#include "stdafx.h"
#include "Idle.h"
#include "Agent.h"


void Idle::onEnter()
{

}

unsigned int Idle::update(void * pObject)
{
	if (m_agent->m_hasFlag == true)
	{
		// OH SHIT, YO TENGO LA BANDERA VAMANOS A LA CHINGADA.
		m_agent->m_fsm.SetState(BOIDSTATE::Base);
		return 0;
	}

	if (m_agent->enemyInSight() != nullptr)
	{
		//OH SHIT, UN ENEMIGO TENGO QUE REVENTARLO
		m_agent->m_fsm.SetState(BOIDSTATE::AttackEnemy);
		return 0;
	}

	Agent* leader = m_agent->leaderInSight();
	if (leader != nullptr)
	{
		// OH SHIT, AHI VA EL LIDER, HAY QUE PROTEGERLO
		m_agent->m_fsm.SetState(BOIDSTATE::DefendLeader);
		return 0;
	}
	else
	{
		// HMM... ¿ENTONCES QUE HAGO?
		float decision = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		if (decision <= 0.5f)
		{
			m_agent->m_fsm.SetState(BOIDSTATE::Attack);
			return 0;
		}
		else {
			m_agent->m_fsm.SetState(BOIDSTATE::DefendBase);
			return 0;
		}
	}
	return 0;
}

void Idle::onExit()
{
}

Idle::~Idle()
{
}
