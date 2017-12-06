#include "stdafx.h"
#include "Aggressive.h"
#include "Agent.h"


void Aggressive::onEnter()
{
	if (m_agent->m_enemyBase != nullptr)
	{
		m_agent->addTarget(m_agent->m_enemyBase, TARGET::Seek);
	}
	else
	{
		m_agent->m_fsm.SetState(BOIDSTATE::Idle);
	}
}

unsigned int Aggressive::update(void * pObject)
{
	Vector3 vec_ToEnemyBase = m_agent->m_enemyBase->m_position - m_agent->m_position;

	if (m_agent->enemyInSight() != nullptr)
	{
		m_agent->m_fsm.SetState(BOIDSTATE::AttackEnemy);
		return 0;
	}

	//¿BASE ENEMIGA A LA VISTA?
	if (vec_ToEnemyBase.magnitud() <= (m_agent->BOID_VISION - 10))
	{
		//¿HAY BANDERA ENEMIGA EN LA BASE?
		Flag* enemyFlag = m_agent->enemyFlagInSight();
		if (enemyFlag != nullptr)
		{
			if (!enemyFlag->m_isEnable)
			{
				m_agent->m_fsm.SetState(BOIDSTATE::Base);
				return 0;
			}
		}
		else {
			m_agent->m_fsm.SetState(BOIDSTATE::Base);
			return 0;
		}

		//SI HAY BANDERA, REVISA SI PUEDE TOMARLA
		if ((enemyFlag->m_position - m_agent->m_position).magnitud() <= m_agent->BOID_RADIUS)
		{
			// TOMA LA BANDERA ENEMIGA, REGRESA A LA BASE AMIGA
			m_agent->m_hasFlag = true;
			enemyFlag->m_isEnable = false;
			m_agent->m_fsm.SetState(BOIDSTATE::Idle);
			return 0;
		}
	}

	// LÍDER A LA VISTA	
	Agent* leader = m_agent->leaderInSight();
	if (leader != nullptr)
	{
		//SEGUIR AL LIDER
		m_agent->m_fsm.SetState(BOIDSTATE::DefendLeader);
	}

	return 0;
}

void Aggressive::onExit()
{
	m_agent->removeTarget(TARGET::Seek);
}



Aggressive::~Aggressive()
{
}
