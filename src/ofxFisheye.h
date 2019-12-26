#pragma once
#include "ofMain.h"
#define GLSL120(shader) "#version 120\n" #shader

class ofxFisheye {
public:
	ofxFisheye();
	~ofxFisheye();

private:
	ofFbo source;
	ofShader shader;
	float fisheyeFactor, scale;
	void makeShader();
	void m_begin();
	void m_end();
	void m_sourceResizeIfChanged();

	static ofxFisheye * singleton;


	// static
public:
	static void begin();
	static void end();
	static void setFisheyeFactor(float);
	static float getFisheyeFactor();
	static void setScale(float);
	static float getScale();

private:
	static void makeSingletonIfDoesntExist();
};

