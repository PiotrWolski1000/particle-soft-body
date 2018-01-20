#include "particles.h"

Particles::Particles() {};
Particles::Particles(float masa = 1, ofVec3f pos = ofVec3f(0, 0, 0), ofVec3f vel = ofVec3f(0, 0, 0), ofVec3f force = ofVec3f(0, 0, 0), int width = 5) {
	this->m = masa;
	this->r = pos;
	this->v = vel;
	this->f = force;
	this->radius = width;
}
int Particles::getRadius()
{
	return this->radius;
}
int Particles::getMass()
{
	return this->m;
}
ofVec3f Particles::getPos()
{
	return this->r;
}

ofVec3f Particles::getVel()
{
	return this->v;
}
ofVec3f Particles::getForce()
{
	return this->f;
}

void Particles::setPos(ofVec3f r2)
{
	this->r.x = r2.x;
	this->r.y = r2.y;
	this->r.z = r2.z;
}

void Particles::setPosX(int value)
{
	this->r.x = value;
}
void Particles::setPosY(int value)
{
	this->r.y = value;
}
void Particles::setPosZ(int value)
{
	this->r.z = value;
}

void Particles::setVelX(int value)
{
	this->v.x = value;
}
void Particles::setVelY(int value)
{
	this->v.y = value;
}
void Particles::setVelZ(int value)
{
	this->v.z = value;
}

void Particles::setForceX(int value)
{
	this->r.x = value;
}
void Particles::setForceY(int value)
{
	this->r.y = value;
}
void Particles::setForceZ(int value)
{
	this->r.z = value;
}
void Particles::setLifespan(double dt)
{
	this->lifespan = dt;
}
double Particles::getLifespan()
{
	return this->lifespan;
}
double Particles::getBornTime()
{
	return this->bornTime;
}
void Particles::setBornTime(double time)
{
	this->bornTime = time;
}
void Particles::move(double dt)
{
	float k = 85.0f;

	this->f.x = 0;
	this->f.z = 0;
	//this->f.y = -10;
	this->f.y = 0;
	
	//velocity update
	this->v.x += this->f.x * dt;
	this->v.y += this->f.y * dt;
	this->v.z += this->f.z * dt;

	//position update
	this->r.x += this->v.x * dt;
	this->r.y += this->v.y * dt;
	this->r.z += this->v.z * dt;

	//what when hit the "floor"?(y == 0)
	//if (this->r.y <= 0) {
	//	this->r.y = 0;
	//}



	





}

void Particles::setStartPosition(ofVec3f position) {
	this->startPosition = position;
}

ofVec3f Particles::getStartPosition() {
	return this->startPosition;
}

void Particles::setIsStatic(bool value)
{
	this->isStatic = value;
}

void Particles::preparePositionVector()
{
	//First position, initial position
	//particlePosition.x.push_back(RandomMinMax(400, 600));
	//particlePosition.y.push_back(ofGetHeight());

	////Secound position
	//particlePosition.x.push_back(particlePosition.x[0] + dt * dt * (particleForce.x / mass));
	//particlePosition.y.push_back(particlePosition.y[0] + dt * dt * (particleForce.y / mass));

	////Third position, Verlet method
	//particlePosition.x.push_back(2 * particlePosition.x[1] - particlePosition.x[0] + dt * dt * (particleForce.x / mass));
	//particlePosition.y.push_back(2 * particlePosition.y[1] - particlePosition.y[0] + dt * dt * (particleForce.y / mass));
}

void Particles::updateVerlet() {
	//if (!isStatic) {
	//	v_positionNew = 2 * v_position - v_positionOld + (dt * dt * v_forces / m_mass);
	//	v_positionOld = v_position;
	//	v_position = v_positionNew;
	//}
}

void Particles::updateEuler() {
	//if (!isStatic) {
	//	v_velocity += v_forces * dt;
	//	v_positionNew = v_position + v_velocity * dt;
	//	v_positionOld = v_position;
	//	v_position = v_positionNew;
	//}
}