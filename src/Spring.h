#pragma once
#include <vector>
#include "Point.h"

class Spring
{
public:
	Spring(int i, int j, std::vector<Point*> &points);
	
	int i, j; //indexes of connected points
	int startPositionXForI, startPositionYForJ;
	float length, nx, ny; //distance between 2 points, normals

	float restLength;
																							
	void setRestLength(float value);
	float getRestLength();

	float getLength();
	void setLength(float length);

	void setNormalVectorX();
	float getNormalVectorX();

	void setNormalVectorY();
	float getNormalVectorY();
};

