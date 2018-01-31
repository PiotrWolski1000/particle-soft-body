#include "ofApp.h"
#include "Point.h"
#include "Spring.h"
#include <iostream>

#define N 360
#define FINAL_PRESSURE 85.0f

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(125, 120, 0);
	ofSetFrameRate(25);
	this->volume = 0.0f;
	this->dt = 0.01f;
	this->G = -10.0f;
	this->k = 85.0f;
	this->d = 35.0f;
	this->counter = 0;
	this->pressure = 0.0f;
	// FFT initialization
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++) {
		fftSmoothed[i] = 0;
	}
	nBands = 128;



	//spring & point inits
	this->initPoints();
	this->initSprings();
	this->musicInit();
}

void ofApp::update() {

	float * val = ofSoundGetSpectrum(nBands);			// request 128 values for fft
	float avgSound = 0;
	for (int i = 0; i < nBands; i++) {
		fftSmoothed[i] *= 0.6f;								// let the smoothed calue sink to zero:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];	// take the max, either the smoothed or the incoming:
		avgSound += fftSmoothed[i];
	}

	cam.setGlobalPosition(ofPoint(500, 500, 1000 + (fftSmoothed[0] * 10)));

	// average loudness
	avgSound /= nBands;

	ofSetBackgroundColor(ofColor(52 + avgSound * 500, 122 + avgSound * 500,159 + avgSound * 500));;
	dt = 0.01* (avgSound-20);
	cout << dt<<'\n';

	//if debug parameter is equals to true, we display info in cmd
	if (this->debug)
		this->debugInfo();

	////gravity
	for (auto &p : myPoints) {

		//p->forces.y = p->mass*G;
		//p->forces.y = p->mass*G*(this->pressure - FINAL_PRESSURE >= 0);
	
		p->forces.y = 0;
		p->forces.x = 0;
	}

	//elascicity force
	for (auto &s : mySprings)
	{
		//distance between 2 points
		Point *p1 = myPoints[s->i];
		Point *p2 = myPoints[s->j];

		float distance = p1->position.distance(p2->position);

		if (distance != 0)
		{
			float vx12 = p1->velocity.x - p2->velocity.x;
			float vy12 = p1->velocity.y - p2->velocity.y;

			float f = (distance - s->length * k + (vx12 * (p1->position.x - p2->position.x) + vy12 * (p1->position.y - p2->position.y)) * d / distance);

			float Fx = ((p1->position.x - p2->position.x) / distance) * f;
			float Fy = ((p1->position.y - p2->position.y) / distance) * f;
			//nx ny

			p1->forces.x -= Fx;
			p1->forces.y -= Fy;

			p1->forces.x += Fx;
			p2->forces.y += Fy;

		}
		s->nx = ((p1->position - p2->position).perpendicular() / (p1->position - p2->position).length()).x;
		s->ny = ((p1->position - p2->position).perpendicular() / (p1->position - p2->position).length()).y;
	}

	//move
	if (counter < 2) {
		for (auto &p : myPoints)
		{
			p->updateEuler(this->dt);
			counter++;
			//cout << "test\n";
		}
	} else {
		for (auto &p : myPoints)
		{
			//cout << "alalala";
			p->updateVerlet(this->dt);
		}
	}
	if (pressure < FINAL_PRESSURE)
	{
		pressure += FINAL_PRESSURE / 100.0f;
	}

	for (auto & s : mySprings) {
		//this->countPressure();
	}

}

void ofApp::draw(){
	cam.begin();
	cam.lookAt(ofVec3f(0, 500, 0));//switch to center of axis coordinates

	//this->drawCoordinates();
	this->drawPoints();
	this->drawAllSprings();	

	cam.end();
}

void ofApp::drawAllSprings()
{
	for (auto const& s : mySprings)
	{
		ofVec2f pos1 = myPoints[s->i]->position;
		ofVec2f pos2 = myPoints[s->j]->position;
		ofSetLineWidth(1);
		ofDrawLine(pos1, pos2);
	}
}

void ofApp::drawPoints() {
	for (auto const &p : myPoints)
		if (p->isStatic == true) {
			ofSetColor(255, 0, 0);
			ofDrawCircle(p->position, 10);
		}
		else {
			ofSetColor(0, 255, 0);
			ofDrawCircle(p->position, 10);
		}
}

void ofApp::initPoints() {
	ofVec2f rotationPoint = ofVec2f(500, 500);
	ofVec2f startElementPosition = ofVec2f(250, 500);
	ofVec2f tempPosition = ofVec2f(0, 0);
	float alfa = 360 / N;

	//first particle is defined with startElementPosition, later on we use matrix rotation
	myPoints.push_back(new Point(startElementPosition.x, startElementPosition.y, 1, false));

	for (int i = 1; i < N; i++) {
		float alfa = 360 / N * i;
		ofVec2f tempPosition = ofVec2f(-((int(startElementPosition.x - rotationPoint.x))*cos(PI / 180 * alfa) + (int(startElementPosition.y - rotationPoint.y))*sin(PI / 180 * alfa)+ rotationPoint.x),//x
			(int(startElementPosition.x - rotationPoint.x))*sin(PI / 180 * alfa) - (int(startElementPosition.y - rotationPoint.y))*cos((PI / 180 * alfa) - rotationPoint.y));
	
		
		myPoints.push_back(new Point(tempPosition.x+rotationPoint.x, tempPosition.y+rotationPoint.y, 1, false));

	}

	for (auto & s : mySprings) {
		Point *p1 = myPoints[s->i];
		Point *p2 = myPoints[s->j];

		float rlength = sqrt(pow(p1->position.x - p2->position.x, 2) + pow(p1->position.y - p2->position.y, 2));

			s->setRestLength(rlength);
	}
}

void ofApp::initSprings() {

	for (int i = 0; i < N-1;i++) {
		mySprings.push_back(new Spring(i, i + 1, myPoints));
	}
	//last spring, which connects last and first particle
	mySprings.push_back(new Spring(N-1, 0, myPoints));

	for (auto &s : mySprings) {
		//distance between 2 points
		Point *p1 = myPoints[s->i];
		Point *p2 = myPoints[s->j];
		//set length
		s->length = sqrt(pow(p1->position.x - p2->position.x, 2) + pow(p1->position.y - p2->position.y, 2));
		cout << "s length: " << s->length << '\n';

		//normal vec
		//ofVec2f normalVector = ofVec2f(p1->position.x - p2->position.x, p2->position.y - p2->position.y);

		//volume of our circle
		this->volume += 0.5 * fabs(p1->position.x - p2->position.x) * (s->nx * s->length);
		cout << "volume: " << s->nx;
	}
}

void ofApp::drawCoordinates() {
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

void ofApp::debugInfo() {
	for (int i = 0; i < N; i++) {
		std::cout << "point: " << i << ", position:  " << myPoints[i]->position<<'\n';
	}

	//std::cout << "ilosc springow: " << mySprings.size()<<'\n';
	//std::cout << "ilosc pointow: " << myPoints.size()<<'\n';
}

void ofApp::musicInit() {
	music.load("bestie.mp3");
	music.setVolume(1.0f);
	music.play();



}

void ofApp::countPressure()
{

	for (auto const &s : mySprings) {
		//p1
		Point *p1 = myPoints[s->i];
		//p2
		Point *p2 = myPoints[s->j];

		float rootDistance = sqrt(
			(pow(p1->position.x - p2->position.x,2)
				+ 
				(pow(p1->position.y - p2->position.y, 2)
				)));
		//float rootDistance = ofVec2f(p1->position).distance(ofVec2f(p2->position));

		//ofVec2f vecNormal = ((p1->position - p2->position).perpendicular()) / rootDistance;
		
		this->volume += 0.5 * fabs(p1->position.x - p2->position.x) * fabs(s->nx) * (rootDistance);
		//cout << rootDistance << '\n';
	}
	for (auto const &s : mySprings)
	{
		//p1
		Point *p1 = myPoints[s->i];
		//p2
		Point *p2 = myPoints[s->j];

		float rootDistance = sqrt(
			(pow(p1->position.x - p2->position.x, 2)
				+
				(pow(p1->position.y - p2->position.y, 2)
					)));//float rootDistance = ofVec2f(p1->position).distance(ofVec2f(p2->position));


		//cout << pressure<<'\n';
		float pressurev = rootDistance * pressure * (1.0f / this->volume);

		//ofVec2f vecNormal = ((p1->position - p2->position).perpendicular()) / rootDistance;


		//p1

		//p1->forces += ofVec2f(s->nx, s->ny) * pressurev;
		p1->forces.x += s->nx * pressurev;
		p1->forces.y += s->ny * pressurev;

		p2->forces.x += s->nx * pressurev;
		p2->forces.y += s->ny * pressurev;


		//p2
		//p2->forces += ofVec2f(s->nx, s->ny) * pressurev;

	}
	

}
