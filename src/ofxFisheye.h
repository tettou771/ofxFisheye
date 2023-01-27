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
    int areaWidth, areaHeight;
	float fisheyeFactor, scale;
	void makeShader();
	void m_begin();
	void m_end();
	void m_sourceResizeIfChanged();

	static ofxFisheye * singleton;


	// static
public:
	static void begin();
    static void setSize(int width, int height);
    static void setWidth(int width);
    static void setHeight(int height);
    static int getWidth();
    static int getHeight();
	static void end();
	static void setFisheyeFactor(float);
	static float getFisheyeFactor();
	static void setScale(float);
	static float getScale();

private:
	static void makeSingletonIfDoesntExist();
};

