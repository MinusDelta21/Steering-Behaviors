#include "stdafx.h"
#include "Attack.h"


void Attack::onEnter()
{
	m_enemy = nullptr;
}

unsigned int Attack::update(void * pObject)
{
	if (m_enemy != nullptr)
	{
		// ¿HE PERDIDO AL ENEMIGO DE MI RADIO DE VISIÓN?
		Vector3 vec_toEnemy = m_enemy->m_position - m_agent->m_position;
		if (vec_toEnemy.magnitud() > m_agent->BOID_VISION)
		{
			// ENEMIGO PERDIDO
			m_enemy = nullptr;
		}

		// ¿TENGO A UN ENEMIGO EN MI RANGO DE DISPARO?
		if (m_agent->enemyInSight())
		{
			// DISPARAR A LO PENDEJO
			m_agent->shootBullet();
		}
	}

	// NO TENGO TARGET
	if (m_enemy == nullptr)
	{
		// BUSCAR UN NUEVO ENEMIGO A LA VISTA.
		m_enemy = m_agent->enemyInSight();

		if (m_enemy != nullptr)
		{
			// HE ENCONTRADO UN NUEVO ENEMIGO
			m_agent->addTarget(m_enemy,TARGET::Seek);
		}
		else
		{
			// NO HAY ENEMIGOS A LA VISTA
			m_agent->m_fsm.SetState(BOIDSTATE::Idle);
		}
	}
	return 0;
}

void Attack::onExit()
{
	m_agent->removeTarget(TARGET::Seek);
}



Attack::~Attack()
{
}
