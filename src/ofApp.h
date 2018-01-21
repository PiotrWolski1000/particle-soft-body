#pragma once

#include "ofMain.h"
#include <vector>
#include "particles.h"
#include "spring.h"

class ofApp : public ofBaseApp{
	float t = 0;
	float volume;

	public:
		void setup();
		void update();
		void draw();
		void initParticles();//create new particles
		void initSprings();

		std::vector<Particles> particles;
		std::vector<Spring> springs;
		void drawCoordinates();
		ofEasyCam cam;
		void musicInit();
		ofSoundPlayer music;
		void updateAllSpringsPosition();

		
};
