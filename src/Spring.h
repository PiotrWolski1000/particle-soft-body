#pragma once
#include "ofMain.h"
#include <math.h>
#include "particles.h"

//#include <ofVec3f.h>
class Spring {
	
	//we have to remember these two coordinates, start from, to coordinates
	ofVec3f from;
	ofVec3f to;
	
	//new from to, when spring is moving 
	//ofVec3f newFrom;
	//float k = 85.0f;
	//float c = 20.0f;//damping constant 
	ofVec3f restLength;

	public:
		Spring() {};
		Spring(ofVec3f from, ofVec3f to);

		void setFrom(ofVec3f position);
		void setTo(ofVec3f position);
		ofVec3f getFrom();
		ofVec3f getTo();
		void drawLine();
		void setRestLength();

		float getLength();

		void countPressure(float volume, Particles& p1, Particles& p2);

		ofVec3f getRestLength();
		void updateSpringPosition(ofVec3f from, ofVec3f to);
		void elasticityForceCounter(Particles& point1, Particles& point2);
		
		ofVec3f countNormalVector(Particles point1, Particles point2);
};