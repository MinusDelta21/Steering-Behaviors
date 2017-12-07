#include "stdafx.h"
#include "Agent.h"
#include "Bullet.h"
#include "GameWindow.h"
#include "Timer.h"


Agent::Agent(GameWindow * gmScn, unsigned int m_team): Boid(gmScn)
{
	this->m_team = m_team;
	if(m_team == 2)	m_tag = "Red Agent";
	else if (m_team == 1) m_tag = "Blue Agent";
	else m_tag = m_team;
	init();
}

Agent::~Agent()
{
}

void Agent::init()
{
	//MAQUINA DE ESTADOS
	m_fsm.AddState(new Idle(this));
	m_fsm.AddState(new Attack(this));
	m_fsm.AddState(new goToBase(this));
	m_fsm.AddState(new DefendCaptured(this));
	m_fsm.AddState(new DefendFlag(this));
	m_fsm.AddState(new Aggressive(this));
	m_fsm.AddState(new Dead(this));
	if (m_team == TEAM::Red) {
		m_texture.loadFromFile("Sprites/youtube.png");
	}
	else {
		m_texture.loadFromFile("Sprites/facebook.png");
	}
	m_sprite.setTexture(m_texture, true);
	m_sprite.setPosition(m_position.x, m_position.y);

	sf::FloatRect rect = m_sprite.getLocalBounds();
	m_sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);
	this->setColor(Vector3(255.f, 255.f, 255.f), 255.f);


	if (m_targetList.size() > 0)
	{
		m_targetList.clear();
	}
	for (unsigned int i = 0; i < (TARGET::Count); ++i) {
		GameObject* newGO = nullptr;
		m_targetList.push_back(newGO);
	}

	m_enemyBase = m_friendlyBase = nullptr;
	vector<Flag*> flagist = m_gameScene->getObjs<Flag>();
	for (int i = 0; i < flagist.size(); ++i)
	{
		if (flagist[i]->m_team == m_team)
		{
			m_friendlyBase = flagist[i];
		}
		else if (flagist[i]->m_team != TEAM::Undefined) {
			m_enemyBase = flagist[i];
		}
	}

	if (m_team == TEAM::Red)
	{
		this->setDirection(1.f, 0.f);
	}
	else
	{
		this->setDirection(-1.f, 0.f);
	}

	m_hasFlag = false;
	m_shoot = 0;

	//ENTRAR EN ESTADO INICIAL
	m_fsm.SetState(BOIDSTATE::Idle);
}

void Agent::update()
{
	m_sprite.setPosition(m_position.x, m_position.y);
	m_fsm.UpdateState(m_gameScene);

	m_shoot = m_shoot + m_gameScene->m_wndTime.getFrameTime();

	m_steeringForce = 0.0f;
	m_steeringForce = m_steeringForce + seekCTF() + fleeCTF() + defendTheLeader();

	if (m_isMoving && !outOfField())
	{
		m_steeringForce = m_steeringForce + obstacleAvoidance(m_gameScene->getObjsInArea<Obstacle>(m_position.x, m_position.y, BOID_VISION))
			+ separation(m_gameScene->getObjsInArea<Boid>(m_position.x, m_position.y, BOID_VISION));
	}
	if (m_isWander)
	{
		m_steeringForce = m_steeringForce + wander();
	}
	if (std::fabsf(m_steeringForce.x) <= std::numeric_limits<float>::epsilon() &&
		std::fabsf(m_steeringForce.y) <= std::numeric_limits<float>::epsilon())return;

	Vector3 steerForceDir = m_steeringForce.normalized();
	m_direction = (m_direction + (steerForceDir * m_gameScene->m_wndTime.getFrameTime()));
	m_direction.normalize();
	m_steeringForce = m_steeringForce.truncate(m_velocity);

	
	m_position = m_position+(m_direction *  m_steeringForce.magnitud() * m_gameScene->m_wndTime.getFrameTime());
	

	m_sprite.setPosition(m_position.x, m_position.y);
	m_sprite.setRotation(m_direction.rad2deg());

	vector<Bullet*> bulletsList = m_gameScene->getObjsInArea<Bullet>(m_position.x, m_position.y, BOID_RADIUS);
	for (auto bullet : bulletsList)
	{
		if (bullet->m_team != m_team)
		{
			m_fsm.SetState(BOIDSTATE::Dead);
			m_gameScene->destroyObject(bullet);
			break;
		}
	}

	if (outOfField())
	{
		m_fsm.SetState(BOIDSTATE::Return);
	}
}

void Agent::render(RenderWindow & wnd)
{
	if (!m_isEnable)
	{
		return;
	}

	wnd.draw(m_sprite);
}

void Agent::destroy()
{
}

bool Agent::outOfField()
{
	if (m_position.x < 20 || m_position.x > 1920 - 20 || m_position.y < 20 || m_position.y > 1080 - 20)
	{
		return true;
	}
	return false;
}

Agent * Agent::leaderInSight()
{
	vector<Agent*> soldierList = m_gameScene->getObjsInArea<Agent>(m_position.x, m_position.y, BOID_VISION);

	for (auto& soldier : soldierList)
	{
		if (soldier->m_team == m_team)
		{
			if (soldier->m_hasFlag && soldier != this)
			{
				return soldier;
			}
		}
	}
	return nullptr;
}

Agent * Agent::enemyInSight()
{
	vector<Agent*> soldierList = m_gameScene->getObjsInArea<Agent>(m_position.x, m_position.y, BOID_VISION);
	for (auto soldier : soldierList)
	{
		if (soldier->m_team != m_team)
		{
			Vector3 vec_distToSoldier = soldier->m_position - m_position;
			if (vec_distToSoldier.dot(m_direction) > 0)
			{
				return soldier;
			}
		}
	}
	return nullptr;
}

Flag * Agent::enemyFlagInSight()
{
	vector<Flag*> flag_list = objectsAtVisionRange<Flag>();
	Flag* enemyFlag = nullptr;

	for (unsigned int i = 0; i < flag_list.size(); ++i)
	{
		if (flag_list[i]->m_team != m_team
			&& flag_list[i]->m_team != TEAM::Undefined)
		{
			enemyFlag = flag_list[i];
			break;
		}
	}
	return enemyFlag;
}

bool Agent::shootBullet()
{
	if (m_shoot > m_reload)
	{
		m_shoot = 0;

		Bullet* bullet = new Bullet(m_position, m_direction, m_gameScene, m_team);
		m_gameScene->addNewObject(bullet);
		return true;
	}
	return false;
}

Vector3 Agent::sceneLitimsForce()
{
	Vector3 pointPos = m_position + (m_direction * BOID_VISION);
	Vector3 force;

	if (pointPos.x < 0)
	{
		force.x = 1;
	}
	else if (pointPos.x > 1920)
	{
		force.x = -1;
	}
	if (pointPos.y < 0)
	{
		force.y = 1;
	}
	else if (pointPos.y > 1080)
	{
		force.y = -1;
	}
	force = force * 9999999.f;

	return force;
}
