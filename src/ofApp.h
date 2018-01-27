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
		
		//inits
		void initPoints();
		void initSprings();
		//lists of  points and springs
		vector<Point*> myPoints;
		vector<Spring*> mySprings;

		//consts
		float G, k, d;	// gravitional, elascicity and dumping coefficients
		
		//other variables & methods
		//displaying information in command line 
		bool debug = true;
		void debugInfo();
		int counter;	// counter for moveUpdate methods(first two steps we're counting with euler)
		float dt;//time step
};

