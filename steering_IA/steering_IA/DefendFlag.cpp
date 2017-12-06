#include "stdafx.h"
#include "DefendFlag.h"
#include "Agent.h"



void DefendFlag::onEnter()
{
}

unsigned int DefendFlag::update(void * pObject)
{
	if (m_agent->enemyInSight() != nullptr)
	{
		//OH SHIT, UN ENEMIGO TENGO QUE REVENTARLO
		m_agent->m_fsm.SetState(BOIDSTATE::AttackEnemy);
		return 0;
	}

	Agent* leader = m_agent->leaderInSight();
	if (leader != nullptr)
	{
		m_agent->m_fsm.SetState(BOIDSTATE::DefendLeader);
		return 0;
	}

	Vector3 vectToBase = ((m_agent->m_friendlyBase)->m_position - m_agent->m_position);
	if (vectToBase.magnitud() >= static_cast<float>(DEFENCE_RANGE))
	{
		//HE SALIDO DEL RANGO RANGO DE DEFENSA.
		m_agent->addTarget(m_agent->m_friendlyBase, TARGET::Seek);
		m_agent->setWander(false);
		return 0;
	}
	else {
		//VIGILAR
		m_agent->removeTarget(TARGET::Seek);
		m_agent->m_isWander = true;
		return 0;
	}
	return 0;
}

void DefendFlag::onExit()
{
	m_agent->removeTarget(TARGET::Seek);
	m_agent->setWander(false);
}

DefendFlag::~DefendFlag()
{
}
