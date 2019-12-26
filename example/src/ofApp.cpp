#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofClear(0);

	// 0:noEffect 1:fisheye
	float factor = (float)ofGetMouseX() / ofGetWidth();
	ofxFisheye::setFisheyeFactor(factor);

	// 1:normal over1:zoomIn
	float scale = (float)ofGetMouseY() / ofGetHeight() + 1.0;
	ofxFisheye::setScale(scale);

	// fisheye effect begin
	ofxFisheye::begin();

	// draw anything
	ofDrawGrid(128, 10, false, false, false, true);

	// fisheye effect begin
	ofxFisheye::end();

	stringstream msg;
	msg << "Please move your mouse" << endl
		<< "x: fisheyeFactor (mouseX): " << factor << endl
		<< "scale (mouseY): " << scale << endl;
	ofDrawBitmapString(msg.str(), 10, 20);
}
