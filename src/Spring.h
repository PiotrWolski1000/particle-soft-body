#pragma once
#include "ofMain.h"

//#include <ofVec3f.h>
class Spring {
	
	ofVec3f from;
	ofVec3f to;
	float k = 85.0f;
	float c = 20.0f;//damping constant 

	public:
		Spring() {};
		Spring(ofVec3f from, ofVec3f to);

		void setFrom(ofVec3f position);
		void setTo(ofVec3f position);
		ofVec3f getFrom();
		ofVec3f getTo();
		void drawLine();


};