#include "spring.h"
Spring::Spring(ofVec3f from, ofVec3f to) {
	this->from = from;
	this->to = to;
}
void Spring::setFrom(ofVec3f position)
{
	this->from = position;
}

void Spring::setTo(ofVec3f position)
{
	this->to = position;
}

ofVec3f Spring::getFrom()
{
	return this->from;
}

ofVec3f Spring::getTo()
{
	return this->to;
}

void Spring::setRestLength()
{
	//this->restLength = this->from.distance(this->to);//by default, it's important to set up possibly best position at constructing spring and particles
	this->restLength = ofVec3f(abs(this->from.x- this->to.x), abs(this->from.y - this->to.y), sqrt(this->from.z - this->to.z));

}

float Spring::getLength()
{
	return (this->from.distance(this->to));
}

void Spring::countPressure(float volume, Particles& point1, Particles& point2)
{
	ofVec2f tempPosPoint1 = ofVec2f(point1.getPos().x, point1.getPos().y);
	ofVec2f tempPosPoint2 = ofVec2f(point2.getPos().x, point2.getPos().y);

	float newLength = getLength();
	ofVec2f normalVec = ((tempPosPoint1 - tempPosPoint2).perpendicular()) / getLength();
	float pressureConst = 0.00001;
	float pressure = newLength * pressureConst * (1.0f / volume);

	ofVec3f normalVec3D = ofVec3f(normalVec.x, normalVec.y, 0);

	//auto value = 0;
	point1.setForce(point1.getForce() + (normalVec3D * pressure));
}

ofVec3f Spring::getRestLength()
{
	return this->restLength;
}

void Spring::updateSpringPosition(ofVec3f from, ofVec3f to)
{
	this->from = from;
	this->to = to;

}

void Spring::elasticityForceCounter(Particles& punkt1, Particles& punkt2)
{
	float newLength = this->getLength();

	float startLength = punkt1.getStartPosition().distance(punkt2.getStartPosition());

	//coefficients elascicity and dump
	float k = 1755 / 1000;
	float d = 15 / 1000;

	float xVel = punkt1.getVel().x - punkt2.getVel().x;//predkosc dla x
	float yVel = punkt1.getVel().y - punkt2.getVel().y;//predkosc dla y
	float zVel = 0;

	float force = (((newLength - startLength) * k) +
		((xVel * (punkt1.getPos().x - punkt2.getPos().x)) + (yVel * (punkt1.getPos().y - punkt2.getPos().y)) * d) / newLength);

	float xForce = (((punkt1.getPos().x - punkt2.getPos().x) / newLength) * force);
	float yForce = (((punkt1.getPos().y - punkt2.getPos().y) / newLength) * force);
	

	punkt1.setForce(ofVec3f(punkt1.getForce().x - xForce, punkt1.getForce().y - yForce, 0));
	punkt2.setForce(ofVec3f(punkt1.getForce().y - xForce, punkt2.getForce().y - yForce, 0));
}

ofVec3f Spring::countNormalVector(Particles point1, Particles point2)
{
	ofVec2f r = ofVec2f(point1.getPos().x - point2.getPos().x, point1.getPos().y - point2.getPos().y);
	return r.perpendicular();
}

ofVec3f Spring::counterOfNormalVector()
{
	ofVec2f r = ofVec2f(this->getFrom().x - this->getTo().x, this->getFrom().y - this->getTo().y);
	return r.perpendicular();
}

void Spring::drawLine()
{
	ofDrawLine(this->from, this->to);
}