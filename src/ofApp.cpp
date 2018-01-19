#include "ofApp.h"
#define N 10//count of particles in spring chain
#define COUNTER 0//counter for first 2 steps of animation with euler equation
//--------------------------------------------------------------
void ofApp::setup(){//run once at the beginning
	ofBackground(0, 0, 0, 0);

	initParticles();
	initSprings();
	
	musicInit();
}

//--------------------------------------------------------------
void ofApp::update(){//main animation loop
	this->t += 0.001;//time and time step, increased by every update loop step by constant value
	
	ofSoundUpdate();//here we can change the music and all the voices we use ein the project
	
	std::cout << "particles count: " << particles.size() << ",\nsprings count: " << springs.size() << '\n';

	for (auto& p : particles)
	{
		p.move(this->t);
	}
	
		this->updateAllSpringsPosition();
}

//--------------------------------------------------------------
void ofApp::draw(){//drawing objects section
	cam.begin();
	cam.lookAt(ofVec3f(0, 0, 0));//switch to center of axis coordinates
	for (int i = 0; i < this->particles.size(); i++) {


		this->drawCoordinates();//coordinates axis lines
		//particles
		ofSetColor(255, 0, 60);
		//particless[i].sphere.setRadius(5);
		particles[i].sphere.setPosition(particles[i].getPos().x, particles[i].getPos().y, particles[i].getPos().z);
		particles[i].sphere.draw();
		//drawing lines
		ofSetColor(243, 255, 115);
		springs[i].drawLine();
	}
	cam.end();
}

void ofApp::initParticles() {

	for (int i = 0; i < N; i++) {
		//int mass = ofRandom(1, 10);
		int mass = ofRandom(1, 1);
		int radius = 5;
		//positions
		//int mRx = i*50;
		int mRx = ofRandom(1, 600);
		//int mRy = i*50;
		int mRy = ofRandom(1, 600);
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

		particles[i].setIsStatic(false);//is not a static particle

		
	}
}

void ofApp::initSprings()
{//here we are creating springs
	for (int i = 0; i < particles.size(); i++) {
		if (i == 0) {//from the last one particle to first spring
			springs.push_back(Spring(particles[particles.size()-1].getPos(), particles[i].getPos()));
		}
		else if (i == particles.size() - 1) {//from the last 
			springs.push_back(Spring(particles[particles.size() - 2].getPos(), particles[particles.size()-1].getPos()));
		}
		else {
			springs.push_back(Spring(particles[i - 1].getPos(), particles[i+1].getPos()));
		}
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

void ofApp::musicInit()
{
	music.load("bestie.mp3");
	music.setVolume(1.0f);
	//music.play();

}

void ofApp::updateAllSpringsPosition()
{
	for (int i = 0; i < particles.size(); i++) {
		if (i > 0 && i != particles.size()-1) {
			springs[i].updateSpringPosition(particles[i-1].getPos(), particles[i].getPos());
		}
		else if(i == particles.size()){//last element, connect to the first one
			springs[i].updateSpringPosition(particles[particles.size() - 1].getPos(), particles[0].getPos());
		}
	}
}
