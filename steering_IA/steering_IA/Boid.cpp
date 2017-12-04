#include "stdafx.h"
#include "Boid.h"
#include <math.h>
#include "Vector3.h"
#define PI					3.141592
#define SEEK_FORCE			30
#define FLEE_RADIUS			50
#define ARRIVE_RADIUS		50
#define PURSUIT_PREDICTION	30
#define NODE_RADIUS			50
#define VELOCITY			50
#define BOID_VISION			50
#define WIDTH				20
#define SEPARATION_RADIUS	50
#define MAX_SEPARATION		50
//Steering Behaviors
Vector3 Boid::seek(int x,int y) {
	return(Vector3(x, y) - m_position).normalized()*SEEK_FORCE;
}
Vector3 Boid::seekCTF()
{
	if (!m_targetList[TARGET::Seek])
		return Vector3();
	return seek(m_targetList[TARGET::Seek]->m_position.x, m_targetList[TARGET::Seek]->m_position.y);
}
Vector3 Boid::flee(int x, int y) {
	if((Vector3(x,y)-m_position).magnitud() < FLEE_RADIUS)
	return this->seek(x, y)*-1;
	else {
		return Vector3(0, 0);
	}
}
Vector3 Boid::fleeCTF()
{
	if (!m_targetList[TARGET::Flee])
		return Vector3();
	return flee(m_targetList[TARGET::Flee]->m_position.x, m_targetList[TARGET::Flee]->m_position.y);
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

Vector3 Boid::defendTheLeader()
{
	if (m_targetList[TARGET::Leader] != nullptr)
	{
		Boid* lead = reinterpret_cast<Boid*>(m_targetList[TARGET::Leader]);
		return (lead->m_direction * SEEK_FORCE * 0.2f) + seek(lead->m_position.x, lead->m_position.y);
	}
	else
	{
		return Vector3();
	}
}

void Boid::setDirection(float x, float y, float z)
{
	m_direction.x = x;
	m_direction.y = y;
	m_direction.z = z;
	m_direction.normalize();
}

Vector3 Boid::getDirection()
{
	return m_direction;
}

void Boid::setVelocity(float vel)
{
	m_velocity = vel;
}

float Boid::getVelocity()
{
	return m_velocity;
}

void Boid::setWander(bool b)
{
	m_isWander = b;
}

Vector3 Boid::getTargetPosition(unsigned int targetIndex)
{
	if (targetIndex >= m_targetList.size()) {
		return Vector3();
	}
	if (m_targetList[targetIndex] != nullptr)
	{
		return Vector3();
	}
	return m_targetList[targetIndex]->m_position;
}

bool Boid::addTarget(GameObject * go, unsigned int targetType, bool _deleteGO)
{
	if (targetType >= m_targetList.size()) {
		return false;
	}
	if (_deleteGO) {
		if (m_targetList[targetType] != nullptr)
		{
			delete m_targetList[targetType];
		}
	}
	m_targetList[targetType] = go;
	return true;
}

bool Boid::removeTarget(unsigned int targetType, bool _deleteGO)
{
	return addTarget(nullptr, targetType, _deleteGO);
}


void Boid::initialize() {
	sf::FloatRect rect = m_sprite.getLocalBounds();
	m_sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);

	if (m_targetList.size() > 0)
	{
		m_targetList.clear();
	}
	for (unsigned int i = 0; i < (TARGET::Count); ++i) {
		GameObject* newGO = nullptr;
		m_targetList.push_back(newGO);
	}
}
void Boid::update() {
	m_steeringForce = 0.0f;
	m_steeringForce = seekCTF() + fleeCTF()	+ obstacleAvoidance(m_gameScene->getObjsInArea<Obstacle>(m_position.x, m_position.y, 25))
		+ defendTheLeader();

	if (m_isWander)
	{
		m_steeringForce = m_steeringForce +  wander();
	}

	if (std::fabsf(m_steeringForce.x) <= std::numeric_limits<float>::epsilon() &&
		std::fabsf(m_steeringForce.y) <= std::numeric_limits<float>::epsilon())
	{//El vector es inválido
		return;
	}

	Vector3 steerForceDir = m_steeringForce.normalized();
	m_direction = (m_direction + (steerForceDir * m_gameScene->m_timer.getFrameTime()));
	m_direction.normalize();
	m_steeringForce = m_steeringForce.truncate(m_velocity);
	m_position += (m_direction *  m_steeringForce.magnitud() * m_gameScene->m_timer.getFrameTime());

	m_sprite.setPosition(m_position.x, m_position.y);
	m_sprite.setRotation(m_direction.rad2deg());
}
void Boid::render() {

}
void Boid::destroy() {

}
Boid::Boid()
{
	init();
}


Boid::~Boid()
{
	destroy();
}
