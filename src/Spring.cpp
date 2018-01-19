#include "Spring.h"
#include "spring.h"

//stare = terazniejsze
//terazniejsze = nowe
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
	//this->restLength = 10.0f;
	this->restLength = this->from.distance(this->to);//by default, it's important to set up possibly best position at constructing spring and particles

}

void Spring::updateSpringPosition(ofVec3f from, ofVec3f to)
{
	this->from = from;
	this->to = to;

}

void Spring::drawLine()
{
	ofDrawLine(this->from, this->to);
}