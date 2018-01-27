#pragma once

#include <vector>
#include "Point.h"

class Spring
{
public:
	Spring(int i, int j, std::vector<Point*> &points);
	~Spring();

	int i, j; //indexes of connected points
	float length, nx, ny; //distance between 2 points, normals
};

