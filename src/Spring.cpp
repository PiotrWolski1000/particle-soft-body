#include "Spring.h"
#include <ofVec2f.h>
#include "Point.h"

Spring::Spring(int i, int j, std::vector<Point*> &points)
{
	this->i = i;
	this->j = j;
	length = points[this->i]->position.distance(points[this->j]->position);
}

Spring::~Spring() {}