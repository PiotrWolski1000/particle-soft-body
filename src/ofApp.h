#pragma once
#include "ofMain.h"
#include "Point.h"
#include "Spring.h"
#include <ofVec2f.h>


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		// drawing functions
		void drawAllSprings(); 
		void drawCoordinates();
		void drawPoints();	   
		
		//pressure
		void countPressure();

		//inits
		void initPoints();
		void initSprings();
		//lists of  points and springs
		vector<Point*> myPoints;
		vector<Spring*> mySprings;

		//consts
		float G, k, d;	// gravitional, elascicity and dumping coefficients
		
		//other variables & methods
		bool debug = false;//if true debugInfo will display information in command line, change to false, when release 
		void debugInfo();//displaying information in command line
		int counter;	// counter for moveUpdate methods(first two steps we're counting with euler)
		float dt;//time step
		float volume;
		float pressure;
		bool gravityOn = false;
		//staff
		ofEasyCam cam;
		ofSoundPlayer music;
		void keyPressed(int key) {
			if (key == 't') {
				if (!this->gravityOn) {
					this->G = -10.0f;
					gravityOn = true;
				}
				else {
					this->G = 0.f;
					gravityOn = false;
				}
				cout << "test!" << G << '\n';
			}
		}
		int nBands = 128;
		float avgSound;
		float* fftSmoothed;

		void musicInit();
};

