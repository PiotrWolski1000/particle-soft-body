#pragma once
#include "ofMain.h"
#include <ofVec3f.h>
#include <math.h>

class Particles {
	float m;
	ofVec3f r;
	ofVec3f v;
	ofVec3f f;
	ofVec3f startPosition;//which are also default position for our springs
	ofVec3f newPosition;
	int radius;
	double lifespan;
	double bornTime;
	bool isStatic;
	//plan
	//this t = clock - lifespan

public:
	Particles();
	Particles(float masa, ofVec3f r, ofVec3f v, ofVec3f f, int radius);
	~Particles() {};

	//moving our particle
	void move(double dt);
	void setStartPosition(ofVec3f position);
	ofVec3f getStartPosition();//start position which is set up while constructing


	//is a static particle? 
	void setIsStatic(bool value);
	bool getIsStatic();

	int getRadius();
	int getMass();

	ofVec3f getPos();//get actuall position of an object
	ofVec3f getVel();
	ofVec3f getForce();

	void setPos(ofVec3f);
	void setForce(ofVec3f);

	void updateVerlet(float);
	void updateEuler(float);

	ofSpherePrimitive sphere;//sphere object 
};




