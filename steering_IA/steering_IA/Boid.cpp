#include "stdafx.h"
#include "Boid.h"
#include <math.h>
#include "Vector3.h"
#define PI					3.141592
#define SEEK_FORCE			3
#define FLEE_RADIUS			5
#define ARRIVE_RADIUS		5
#define PURSUIT_PREDICTION	3
#define NODE_RADIUS			5
#define VELOCITY			5
#define BOID_VISION			5
#define WIDTH				2
#define SEPARATION_RADIUS	5
#define MAX_SEPARATION		5
//Steering Behaviors
Vector3 Boid::seek(int x,int y) {
	return(Vector3(x, y) - m_position).normalized()*SEEK_FORCE;
}
Vector3 Boid::flee(int x, int y) {
	if((Vector3(x,y)-m_position).magnitud() < FLEE_RADIUS)
	return this->seek(x, y)*-1;
	else {
		return Vector3(0, 0);
	}
}
Vector3 Boid::arrive(int x, int y) {
	if((Vector3(x, y) - m_position).magnitud() < ARRIVE_RADIUS) {
		return this->seek(x,y)* ((Vector3(x, y) - m_position).magnitud() / ARRIVE_RADIUS);
	}
	else return this->seek(x, y);
}
Vector3 Boid::pursuit(Vector3 position,Vector3 direction, int speed) {
	float t = (position - m_position).magnitud() / VELOCITY;
	Vector3 futurePos = position + (direction * speed *t);
	return seek(futurePos.x, futurePos.y);
}
Vector3 Boid::evade(Vector3 position, Vector3 direction, int speed) {
	float t = (position - m_position).magnitud() / VELOCITY;
	Vector3 futurePos = position + (direction * speed *t);
	return flee(futurePos.x, futurePos.y);
}
Vector3 Boid::wander() {
	Vector3 circlePos = this->m_position +this->m_direction.normalized() * 3;
	int circleRadius = 1;
	int anguloApertura = 90;
	int selectedAng = (rand() % anguloApertura);
	int anguloDir = atan(m_direction.y / m_direction.x);
	int minAng = anguloDir - (anguloApertura >> 1);
	m_direction = ((circlePos.x + (circleRadius*cos((minAng + selectedAng)*(PI/180)))),
				  (circlePos.y + (circleRadius*sin((minAng + selectedAng*(PI / 180))))));
	return m_direction;
}
Vector3 Boid::followPath(const vector<Vector3>&nodes, int index) {
	if ((Vector3(nodes[index].x, nodes[index].y, nodes[index].z) - m_position).magnitud() > NODE_RADIUS) {
		if (index == 0)
			return this->seek(nodes[0].x, nodes[0].y);
		else {
			Vector3 A = Vector3(nodes[index].x, nodes[index].y, nodes[index].z) - m_position;
			Vector3 B = (0, 0, 0);
			if (index != nodes.size()) 
				Vector3 B = Vector3(nodes[index + 1].x, nodes[index + 1].y, nodes[index + 1].z) - Vector3(nodes[index].x, nodes[index].y, nodes[index].z);
			else 
				Vector3 B = Vector3(nodes[0].x, nodes[0].y, nodes[0].z) - Vector3(nodes[index].x, nodes[index].y, nodes[index].z);
			float esc = A.dot(B);
			Vector3 C = B*esc;
			Vector3 D = B - m_position;
			Vector3 E = A - B;
			return (D - E);
		}
	}
		
	return 0;
}
Vector3 Boid::obstacleAvoidance(vector<Obstacle*>& obstacles) {
	Vector3 visionVec = m_direction * BOID_VISION;
	Vector3 obs_to_vision;
	GameObject *nearestObstacle = NULL;
	float refEsc = BOID_VISION;
	float dotEsc = 0;
	Vector3 vec_to_obs;
	for (int i = 0; i < obstacles.size(); ++i) {
		vec_to_obs = (*obstacles[i]).m_position - this->m_position;
		dotEsc = vec_to_obs.dot(visionVec);
		if ((dotEsc> 0)&& (dotEsc <= 1)&& dotEsc <= refEsc) {
			obs_to_vision = (visionVec*dotEsc) - vec_to_obs;
			if ((obs_to_vision.magnitud() - (*obstacles[i]).m_radius) <= (WIDTH / 2)) {
				nearestObstacle = obstacles[i];		
			}
		}
	}
	if (nearestObstacle != NULL) {
		vec_to_obs = (*nearestObstacle).m_position - this->m_position;
		dotEsc = vec_to_obs.dot(visionVec);
		obs_to_vision = (visionVec * dotEsc) - vec_to_obs;
		return obs_to_vision * 999999.0f;
	}
	else return (0, 0, 0);
}

Vector3 Boid::directionAvg(vector<Boid*>& boidList)
{
	Vector3 dirAvg(0, 0, 0);
	for (int i = 0; i < boidList.size(); ++i) {
		dirAvg =dirAvg + boidList[i]->m_direction;
	}
	return  (dirAvg / boidList.size()).normalized();
}

Vector3 Boid::cohesion(vector<Boid*>& boidList)
{
	Vector3 posAvg(0, 0, 0);
	for (int i = 0; i < boidList.size(); ++i) {
		posAvg = posAvg + boidList[i]->m_position;
	}
	posAvg = posAvg / boidList.size();
	return seek(posAvg.x, posAvg.y);
}

Vector3 Boid::separation(vector<Boid*>& boidList)
{
	Vector3 repForce(0, 0, 0);
	Vector3 vec_to_obj;
	for (int i = 0; i < boidList.size(); ++i) {
		vec_to_obj = (m_position - boidList[i]->m_position);
		if (vec_to_obj.magnitud() <= SEPARATION_RADIUS) {
			repForce = repForce + (vec_to_obj.normalized()*(((1 - vec_to_obj.magnitud()) / SEPARATION_RADIUS) * MAX_SEPARATION));
		}
	}
	return repForce;
}

Vector3 Boid::flock(vector<Boid*>& boidList)
{
	Vector3 flockForce;
	flockForce = this->directionAvg(boidList) + this->cohesion(boidList) + this->separation(boidList);
	return flockForce;
}
Vector3 Boid::followLeader(vector<Boid*>&boidList) {
	Vector3 followForce;
	followForce = this->flock(boidList) + flee(this->m_position.x, this->m_position.y);
	return (0, 0, 0);
}


void Boid::initialize() {

}
void Boid::update() {

}
void Boid::render() {

}
void Boid::destroy() {

}
Boid::Boid()
{
}


Boid::~Boid()
{
}
