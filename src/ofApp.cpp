#include "ofApp.h"
#include "Point.h"
#include "Spring.h"
#include <iostream>

#define N 10

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0, 0, 0);
	ofSetFrameRate(60);

	this->dt = 0.01;
	this->G = 90;
	this->k = 1755.0;
	this->d = 35.0;
	this->counter = 0;
	
	//spring & point inits
	this->initPoints();
	this->initSprings();
}

void ofApp::update(){
	
	//if debug parameter is equals to true, we display info in cmd
	if(this->debug)
		this->debugInfo();
	
	// grawitacja
	for (auto &p : myPoints)
	{
		p->forces.y = p->mass*G;
		p->forces.x = 0;
	}
		
	//elascicity force
	for (auto &s : mySprings)
	{
		//distance between 2 points
		Point *p1 = myPoints[s->i];		
		Point *p2 = myPoints[s->j];
		
		ofVec2f pos1 = p1->position;
		ofVec2f pos2 = p2->position;
		
		float distance = pos1.distance(pos2);

		if (distance != 0)
		{
			//velocities 
			p1->velocity = p1->position - p1->positionOld;
			p2->velocity = p2->position - p2->positionOld;
			ofVec2f v12d = p1->velocity - p2->velocity;	//velocity difference
			ofVec2f r12d = pos1 - pos2;//position difference 
			
			//forces
			ofVec2f f = (distance - s->length) * k + (v12d * r12d) * d / distance;
			ofVec2f F = f * (r12d / distance);
			p1->forces -= F;
			p2->forces += F;
		}
	}

	//move
	if (counter < 2)
		for (auto &p : myPoints)
		{
			p->updateEuler(this->dt);
			counter++;
		}
	else
		for (auto &p : myPoints)
		{
			p->updateVerlet(this->dt);
		}
}

void ofApp::draw(){
	this->drawCoordinates();
	this->drawPoints();
	this->drawAllSprings();	
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
	ofVec2f rotationPoint = ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2);
	ofVec2f startElementPosition = ofVec2f((ofGetWidth() / 2)+250, ofGetHeight() / 2);
	ofVec2f tempPosition = ofVec2f(0, 0);
	float alfa = 360 / N;

	//first particle is defined with position, later we use matrix rotation
	myPoints.push_back(new Point(startElementPosition.x, startElementPosition.y, 1, true));

	for (int i = 1; i < N; i++) {

		ofVec2f tempPosition = ofVec3f(((int(startElementPosition.x - rotationPoint.x))*cos(PI / 180 * alfa*i) + (int(startElementPosition.y - rotationPoint.y))*sin(PI / 180 * alfa*i) + rotationPoint.x),//x
			(int(startElementPosition.x - rotationPoint.x))*sin(PI / 180 * alfa*i) - (int(startElementPosition.y - rotationPoint.y))*cos((PI / 180 * alfa*i) - rotationPoint.y));

		myPoints.push_back(new Point(tempPosition.x, tempPosition.y, 1, false));

		//std::cout << "point: " << i << ", position:  " << myPoints[i]->position<<'\n';
	}
}


void ofApp::initSprings() {

	for (int i = 0; i < N-1;i++) {
		mySprings.push_back(new Spring(i, i + 1, myPoints));
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
	std::cout << "ilosc springow: " << mySprings.size()<<'\n';
	std::cout << "ilosc pointow: " << myPoints.size()<<'\n';
}
