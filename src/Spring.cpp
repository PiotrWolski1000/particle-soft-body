#include "Spring.h"
#include "..\spring.h"
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
	this->restLength = (this->from^int(2) - this->to^int(2));
}

void Spring::drawLine()
{
	ofDrawLine(this->from, this->to);
}