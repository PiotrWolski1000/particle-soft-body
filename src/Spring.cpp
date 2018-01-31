#include "Spring.h"
#include <ofVec2f.h>
#include "Point.h"

Spring::Spring(int i, int j, std::vector<Point*> &points) {
	this->i = i;
	this->j = j;
	length = points[this->i]->position.distance(points[this->j]->position);
}
void Spring::setRestLength(float value) {
	this->restLength = value;	
}
float Spring::getRestLength() {
	return this->restLength;
}
float Spring::getLength() {
	return this->length;
}

void Spring::setLength(float length) {
	this->length = length;
}


float Spring::getNormalVectorX() {
	return this->nx;
}

float Spring::getNormalVectorY() {
	return this->ny;
}
