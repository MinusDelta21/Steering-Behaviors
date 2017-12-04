#pragma once
#include "Boid.h"
#include "StateMachine.h"
#include "Flag.h"

class GameWindow;

class Agent : public Boid
{
	StateMachine m_stateMchn;
	const float		m_reload = 1.0f;
	float			m_shoot;
public:
	Flag* m_enemyBase;
	Flag* m_friendlyBase;
	bool m_hasFlag;
	unsigned int	m_team;
	void	init();
	void	update();
	void	render(RenderWindow& wnd);
	void	destroy();
	bool	outOfField();
	
	Agent* leaderInSight();
	Agent* enemyInSight();
	Flag* enemyFlagInSight();
	bool shootBullet();
	Vector3	sceneLitimsForce();

	bool		m_isMoving;
	Vector3	m_respawnPosition;

	template<class _obj> vector<_obj*> objectsAtVisionRange();

	Agent(GameWindow* gmScn, unsigned int m_team = TEAM::Blue);
	~Agent();
};
template<class _obj>
inline vector<_obj *> Agent::objectsAtVisionRange()
{
	return this->m_gameScene->getObjsInArea<_obj>(m_position.x, m_position.y, BOID_VISION);
}


