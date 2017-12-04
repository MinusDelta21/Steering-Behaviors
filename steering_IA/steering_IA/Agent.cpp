#include "stdafx.h"
#include "Agent.h"
#include "Bullet.h"




Agent::Agent(GameWindow * gmScn, unsigned int m_team)
{
	init();
}

Agent::~Agent()
{
}

void Agent::init()
{
	//MAQUINA DE ESTADOS
	/*m_fsm.AddState(new CIdle(this));
	m_fsm.AddState(new CAttack(this));
	m_fsm.AddState(new CToBase(this));
	m_fsm.AddState(new CReturnToField(this));
	m_fsm.AddState(new CDefendLeader(this));
	m_fsm.AddState(new CDefendBase(this));
	m_fsm.AddState(new CAttackEnemy(this));
	m_fsm.AddState(new CDead(this));*/

	m_texture.loadFromFile("gameResources/sprites/" + static_cast<string>(m_team == TEAM::Red ? "spr_soldier_red.png" : "spr_soldier_green.png"));
	m_sprite.setTexture(m_texture, true);
	m_sprite.setPosition(m_position.x, m_position.y);

	sf::FloatRect rect = m_sprite.getLocalBounds();
	m_sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);
	this->setColor(Vector3(255.f, 255.f, 255.f), 255.f);
	/*
	m_miniFlag_texture.loadFromFile("gameResources/sprites/spr_miniFlag_01.png");
	m_miniFlag_Sprite.setTexture(m_miniFlag_texture, true);
	m_miniFlag_Sprite.setColor((m_team == TEAM::kRed ? Color::Green : Color::Red));*/

	//PARAMETROS DE OBJETIVOS
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

	// VARIOS
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
	m_fsm.UpdateState(m_gameScene);

	if (!m_isEnable)
	{
		// NO ESTÁ ACTIVADO, SOLO DEFINIR LA POSICIÓN DEL SPRITE.
		m_sprite.setPosition(m_position.x, m_position.y);
		return;
	}

	// AUMENTAR EL CONTADOR DE TIEMPO;
	m_shoot = m_shoot + m_gameScene->m_time.getFrameTime();

	// CALCULO DE FUERZAS
	m_steeringForce = 0.0f;
	m_steeringForce = m_steeringForce + seekCTF() + fleeCTF() + defendTheLeader();

	if (m_isMoving && !outOfField())
	{
		// SI ME ESTOY MOVIENDO, EVITAR OBSTÁCULOS Y SEPARARME DE MIS COMPAS.
		m_steeringForce = m_steeringForce + obstacleAvoidance(m_gameScene->getObjsInArea<Obstacle>(m_position.x, m_position.y, BOID_VISION))
			+ separation(m_gameScene->getObjsInArea<Boid>(m_position.x, m_position.y, BOID_VISION));
	}
	if (m_isWander)
	{
		m_steeringForce = m_steeringForce + wander();
	}

	if (std::fabsf(m_steeringForce.x) <= std::numeric_limits<float>::epsilon() &&
		std::fabsf(m_steeringForce.y) <= std::numeric_limits<float>::epsilon())
	{//El vector es inválido
		return;
	}

	Vector3 steerForceDir = m_steeringForce.normalized();
	m_direction = (m_direction + (steerForceDir * m_gameScene->m_time.getFrameTime()));
	m_direction.normalize();
	m_steeringForce = m_steeringForce.truncate(m_velocity);

	if (m_isMoving)
	{
		// APLICAR FUERZAS SOLO SI ESTOY EN MOVIMIENTO.
		m_position += (m_direction *  m_steeringForce.magnitud() * m_gameScene->m_time.getFrameTime());
	}

	m_sprite.setPosition(m_position.x, m_position.y);
	m_sprite.setRotation(m_direction.rad2deg());

	// REVISAR SI UNA BALA ENEMIGA ME HA GOLPEADO
	vector<Bullet*> bulletsList = m_gameScene->getObjsInArea<Bullet>(m_position.x, m_position.y, BOID_RADIUS);
	for (auto bullet : bulletsList)
	{
		if (bullet->m_team != m_team)
		{
			// RAYOS, ESTOY MUERTO.
			m_fsm.SetState(BOIDSTATE::Dead);
			m_gameScene->destroyObject(bullet);
			break;
		}
	}

	// SI POSEE LA BANDERA, DEFINIR POSICIÓN DEL SPRITE.
	if (m_hasFlag)
	{
		m_miniFlag_Sprite.setPosition(m_position.x + (BOID_RADIUS >> 1), m_position.y - (BOID_RADIUS >> 1));
	}

	// SI EL SOLDADO ESTÁ FUERA DEL CAMPO DE BATALLA.
	if (outOfField())
	{
		m_fsm.SetState(BOIDSTATE::ToField);
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
