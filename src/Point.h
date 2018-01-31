#pragma once
#include <ofVec2f.h>

class Point
{
public:
	Point(float x, float y, float mass, bool isStatic);
	//radius
	int radius = 250;
	void updateVerlet(float);
	void updateEuler(float);



	ofVec2f positionOld;
	ofVec2f position;
	ofVec2f positionNew;

	ofVec2f velocity; 
	ofVec2f forces;
	float mass;
	bool isStatic;
};

