#include "ofApp.h"
#define N 10//

//--------------------------------------------------------------
void ofApp::setup(){//run once at the beginning
	init();
}

//--------------------------------------------------------------
void ofApp::update(){//main animation loop
	this->t += 0.01;//time and time step, increased by every update loop step by constant value

	for (auto& p : particles)
	{
		p.move(this->t);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){//drawing objects section
	cam.begin();
	cam.lookAt(ofVec3f(0, 0, 0));//switch to center of axis coordinates
	for (int i = 0; i < this->particles.size(); i++) {


		this->drawCoordinates();//coordinates axis lines
		//particles
		//ofSetColor(255, 0, 0,b[i].getLifespan()/12.0 * 255);
		ofSetColor(128, 128, 128);
		//particless[i].sphere.setRadius(5);
		particles[i].sphere.setPosition(particles[i].getPos().x, particles[i].getPos().y, particles[i].getPos().z);
		particles[i].sphere.draw();
		//drawing lines
		//if(!i==particles.size())
		//springs[i].drawLine();
	}
	cam.end();
}

void ofApp::init() {
	for (int i = 0; i <= N; i++) {
		//int mass = ofRandom(1, 10);
		int mass = ofRandom(1, 1);
		int radius = 5;
		//positions
		int mRx = i*50;
		//int mRx = 0;
		int mRy = i*50;
		int mRz = 0;
		//velocities
		int mVx = 0;
		int mVy = 0;
		int mVz = 0;

		//forces, null at start
		int mFx = 0;
		int mFy = 0;
		int mFz = 0;

		particles.push_back(Particles(mass, ofVec3f(mRx, mRy, mRz), ofVec3f(mVx, mVy, mVz), ofVec3f(mFx, mFy, mFz), radius));
		particles[i].setStartPosition(ofVec3f(mRx, mRy, mRz));


		//here we are creating springs
		if (i > 0) {
			if(i<particles.size()-1){
			ofVec3f tempPosFrom = ofVec3f(particles[i - 1].getStartPosition());
			ofVec3f tempPosTo = ofVec3f(particles[i].getStartPosition());
			springs.push_back(Spring(tempPosFrom, tempPosTo));
			}else {//when iteration hits the last spring
				//here we want to connect last particle with the first one
				ofVec3f tempPosFrom = particles[particles.size() - 1].getStartPosition();
				ofVec3f tempPosTo = particles[0].getStartPosition();
				springs.push_back(Spring(tempPosFrom, tempPosTo));

			}
		}
		
		//particless[i].setBornTime(clock());
		//particless[i].setLifespan(ofRandom(12.0));
	}
}

void ofApp::drawCoordinates()
{
	//red color- x-axis
	ofSetColor(255, 0, 0);
	ofDrawLine(0, 0, 0, 100000, 0, 0);
	//green- y-axis
	ofSetColor(0, 255, 0);
	ofDrawLine(0, 0, 0, 0, 100000, 0);
	//blue z-axis
	ofSetColor(0, 0, 255);
	ofDrawLine(0, 0, 0, 0, 0, 100000);
}