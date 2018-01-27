#include "Point.h"
#include <ofGraphics.h>


Point::Point(float x, float y, float mass, bool isStatic)
{
	
	this->positionOld = {x, y };
	this->position = { x,y };
	this->velocity = { 0,0 };
	this->forces = { 0,0 };
	this->mass = mass;
	this->isStatic = isStatic;

}


void Point::updateVerlet(float dt)
{
	if (!isStatic)
	{
		positionNew = 2 * position - positionOld + (dt*dt*forces / mass);
		positionOld = position;
		position = positionNew;
	}
}

void Point::updateEuler(float dt)
{
	if (!isStatic)
	{
		velocity += forces * dt;
		positionNew = position + velocity * dt;
		positionOld = position;
		position = positionNew;
	}
}
