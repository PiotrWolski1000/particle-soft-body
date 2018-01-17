#pragma once

#include "ofMain.h"
#include "particles.h"
#include "spring.h"
#include <vector>

class ofApp : public ofBaseApp{
	float t = 0;

	public:
		void setup();
		void update();
		void draw();
		void init();//create new particles
		std::vector<Particles> particles;
		std::vector<Spring> springs;
		void drawCoordinates();
		ofEasyCam cam;

		
};
