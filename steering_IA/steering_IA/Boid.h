#pragma once
#include "GameObject.h"
#include <vector>
#include "Obstacle.h"
using std::vector;

class Boid : public GameObject
{
	Vector3 m_direction;
	int m_followIndex;
public:
	//Steering Behaviors
	Vector3 seek(int x,int y);
	Vector3 flee(int x, int y);
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
	void initialize();
	void update();
	void render();
	void destroy();
	Boid();
	~Boid();
};

