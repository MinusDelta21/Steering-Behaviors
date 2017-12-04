#pragma once
#include "SpriteRenderer.h"
#include <vector>
#include "Obstacle.h"
#include "StateMachine.h"
using std::vector;
using sf::RenderWindow;
using sf::Texture;
using sf::Sprite;
using sf::Vertex;
using sf::CircleShape;
using sf::Vector2f;
using sf::Font;
using sf::Text;
using std::vector;
using std::to_string;

namespace TARGET {
	enum t {
		Undefined,
		Seek,
		Flee,
		Leader,
		Count
	};
}

class Vector3;
class GameWindow;
class Obstacle;
class StateMachine;
class State;
class Boid : public SpriteRenderer
{
public:
	Vector3 m_steeringForce;
	Vector3 m_direction;
	float m_velocity;
	int m_followIndex;
	GameWindow* m_gameScene;
	StateMachine m_fsm;
	State*		m_activeState;
	float		m_timeTrigger;
	float		m_timeCount;
	vector<GameObject*>	m_targetList;
	bool					m_isWander;
	//Forces
	static const int SEEK_FORCE = 150;
	static const int BOID_RADIUS = 25;
	static const int BOID_VISION = 275;
	//Steering Behaviors
	Vector3 seek(int x,int y);
	Vector3	seekCTF();
	Vector3 flee(int x, int y);
	Vector3	fleeCTF();
	Vector3 arrive(int x, int y);
	Vector3 pursuit(Vector3 position, Vector3 direction, int speed);
	Vector3 evade(Vector3 position, Vector3 direction, int speed);
	Vector3 wander();
	Vector3 followPath(const vector<Vector3>&nodes, int index);
	Vector3 obstacleAvoidance(vector<Obstacle*>& obstacles);
	Vector3 directionAvg(vector<Boid*>&boidList);
	Vector3 cohesion(vector<Boid*>&boidList);
	Vector3 separation(vector<Boid*>&boidList);
	Vector3 flock(vector<Boid*>&boidList);
	Vector3 followLeader(vector<Boid*>&boidList);
	Vector3	defendTheLeader();
	//
	void setDirection(float x, float y, float z = 0);
	Vector3	getDirection();
	void setVelocity(float vel);
	float getVelocity();
	void setWander(bool b);
	Vector3 getTargetPosition(unsigned int targetIndex);
	bool addTarget(GameObject* go, unsigned int targetType, bool _deleteGO = false);
	bool removeTarget(unsigned int targetType, bool _deleteGO = false);

	void initialize();
	void update();
	void render();
	void destroy();
	Boid(GameWindow* gmScn);
	~Boid();
};

