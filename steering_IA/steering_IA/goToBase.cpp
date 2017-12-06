#include "stdafx.h"
#include "goToBase.h"
#include "Agent.h"
#include "GameWindow.h"

void goToBase::onEnter()
{
	if (m_agent->m_enemyBase != nullptr)
	{
		m_agent->addTarget(m_agent->m_friendlyBase, TARGET::Seek);
	}
}

unsigned int goToBase::update(void * pObject)
{
	Vector3 vec_ToFriendlyBase = m_agent->m_friendlyBase->m_position - m_agent->m_position;
	GameWindow* gmScn = reinterpret_cast<GameWindow*>(pObject);


	//¿HE LLEGADO A LA BASE?
	if (vec_ToFriendlyBase.magnitud() <= m_agent->BOID_RADIUS)
	{
		// ¿POSEO LA BANDERA ENEMIGA?
		if (m_agent->m_hasFlag) {
			vector<Flag*> flags = gmScn->getObjs<Flag>();

			for (int i = 0; i < flags.size(); ++i)
			{
				if (flags[i]->m_team != m_agent->m_team)
				{
					if (!flags[i]->m_isEnable)
					{
						flags[i]->m_isEnable = true;
						break;
					}
				}
			}
			m_agent->m_hasFlag = false;
		}
		// REGRESO A IDLE
		m_agent->m_fsm.SetState(BOIDSTATE::Idle);
		return 0;
	}


	if (m_agent->m_hasFlag)
	{
		return 0;
	}

	if (m_agent->enemyInSight() != nullptr)
	{
		//OH SHIT, UN ENEMIGO TENGO QUE REVENTARLO
		m_agent->m_fsm.SetState(BOIDSTATE::AttackEnemy);
		return 0;
	}

	//¿LIDER A LA VISTA?
	Agent* leader = m_agent->leaderInSight();
	if (leader != nullptr)
	{
		m_agent->m_fsm.SetState(BOIDSTATE::DefendLeader);
		return 0;
	}

	//¿HAY BANDERA ENEMIGA EN LA BASE?
	Flag* enemyFlag = m_agent->enemyFlagInSight();
	if (enemyFlag != nullptr)
	{
		if (enemyFlag->m_isEnable)
		{
			// VAMOS POR LA BANDERA CARAJO!
			m_agent->m_fsm.SetState(BOIDSTATE::Attack);
			return 0;
		}
	}

	return 0;
}

void goToBase::onExit()
{
}

goToBase::~goToBase()
{
}
