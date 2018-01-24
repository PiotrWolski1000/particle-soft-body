#include "ofApp.h"
#define N 10 //count of particles in spring chain
#define COUNTER 0//counter for first 2 steps of animation with euler equation
//--------------------------------------------------------------
void ofApp::setup(){//run once at the beginning
	ofBackground(0, 0, 0, 0);
	ofSetFrameRate(10);

	volume = 0;

	initParticles();
	initSprings();
	
	musicInit();
}

//--------------------------------------------------------------
void ofApp::update(){//main animation loop
	this->t += 0.001;//time and time step, increased by every update loop step by constant value
	
	ofSoundUpdate();//here we can change the music and all the voices we use in the project
	
	std::cout << "particles count: " << particles.size() << ",\nsprings count: " << springs.size() << '\n';

	for (int i = 0; i < N; i++) {
		this->particles[i].move(this->t);
		

		if(i == 0){
			this->springs[i].Spring::elasticityForceCounter(this->particles[this->particles.size()-1], this->particles[1]);
			this->springs[i].Spring::countPressure(this->volume, this->particles[particles.size() - 1], this->particles[1]);
		}
		else if (i == particles.size() - 1) {
			this->springs[i].Spring::elasticityForceCounter(this->particles[this->particles.size() - 2], this->particles[0]);
			this->springs[i].Spring::countPressure(this->volume, this->particles[this->particles.size() - 2], this->particles[0]);
		}
		else {
			this->springs[i].Spring::elasticityForceCounter(this->particles[i-1], this->particles[i]);
			this->springs[i].Spring::countPressure(this->volume, this->particles[i - 1], this->particles[i]);
		}
	}


		this->updateAllSpringsPosition();
}

//--------------------------------------------------------------
void ofApp::draw(){//drawing objects section
	cam.begin();
	cam.lookAt(ofVec3f(500, 0, 0));//switch to center of axis coordinates
	for (int i = 0; i < this->particles.size(); i++) {


		this->drawCoordinates();//coordinates axis lines
		//particles
		if (i == 0)
			ofSetColor(255, 0, 60);
		else
			ofSetColor(255, 255, 255);
		//particless[i].sphere.setRadius(5);
		this->particles[i].sphere.setPosition(particles[i].getPos().x, particles[i].getPos().y, particles[i].getPos().z);
		this->particles[i].sphere.draw();
		//drawing lines
		ofSetColor(243, 255, 115);
		this->springs[i].drawLine();
	}
	cam.end();
}

void ofApp::initParticles() {

	ofVec3f rotationPoint = ofVec3f(500, 500, 0);
	ofVec3f startElementPosition = ofVec3f(750, 500, 0);
	ofVec3f tempPosition = ofVec3f(0, 0 , 0);
	float alfa = 360/N;

	for (int i = 0; i < N; i++) {
		int mass = ofRandom(1, 10);
		//int mass = 100;
		int radius = 1;
		alfa = 360/N * i;
		//positions
		//rotation matrix
		tempPosition = ofVec3f(((int(startElementPosition.x - rotationPoint.x))*cos(PI / 180 * alfa) + (int(startElementPosition.y - rotationPoint.y))*sin(PI / 180 * alfa) + rotationPoint.x),//x
			(int(startElementPosition.x - rotationPoint.x))*sin(PI / 180 * alfa) - (int(startElementPosition.y - rotationPoint.y))*cos((PI / 180 * alfa )- rotationPoint.y),//y
			0);//z
		//create and setting up the particles
		particles.push_back(Particles(mass, tempPosition, ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), radius));
		particles[i].setStartPosition(tempPosition);
		
		//only first element is static for now 
		if(i == 0)
			particles[i].setIsStatic(true);//is not a static particle
		else
			particles[i].setIsStatic(false);
	}
}

void ofApp::initSprings()
{//here we are creating springs
	for (int i = 0; i < particles.size(); i++) {
		if (i == 0) {//from the last one particle to first spring
			this->springs.push_back(Spring(this->particles[this->particles.size() - 1].getPos(), this->particles[0].getPos()));
		}
		else if (i == particles.size() - 1) {//from the last 
			this->springs.push_back(Spring(particles[this->particles.size() - 2].getPos(), this->particles[particles.size() - 1].getPos()));
		}
		else {
			this->springs.push_back(Spring(this->particles[i - 1].getPos(), this->particles[i + 1].getPos()));
		}
		this->volume += 0.5 * fabs(this->springs[i].getFrom().x - this->springs[i].getTo().x) * (springs[i].counterOfNormalVector().x * springs[i].getLength());
		this->springs[i].setRestLength();
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
		if (i == 0) {
			this->springs[i].updateSpringPosition(particles[particles.size() - 1].getPos(), particles[i].getPos());
		}
		else if (i == particles.size()) {//last element, connect to the first one
			this->springs[i].updateSpringPosition(particles[particles.size() - 2].getPos(), particles[0].getPos());
		}
		else
			this->springs[i].updateSpringPosition(this->particles[i - 1].getPos(), this->particles[i].getPos());
	}
}
