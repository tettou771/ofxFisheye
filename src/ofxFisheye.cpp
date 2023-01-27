#include "ofxFishEye.h"

ofxFisheye * ofxFisheye::singleton = nullptr;

ofxFisheye::ofxFisheye() {
	fisheyeFactor = 1.0;
	scale = 1.0;
    areaWidth = 1;
    areaHeight = 1;
	makeShader();
}


ofxFisheye::~ofxFisheye() {
}

void ofxFisheye::makeShader() {
	string fragmentShader = GLSL120(

		uniform sampler2DRect source;
	uniform float radius;
	uniform float fisheyeFactor;
	uniform float scale;
	uniform vec2 center;

	float half_pi = 1.570796326794897;

	void main(void) {
		vec2 fromCenter = gl_FragCoord.xy - center;
		fromCenter.y = - fromCenter.y;
		float distSquared = dot(fromCenter, fromCenter);
		if (distSquared < radius * radius * scale * scale) {
			float dist = sqrt(distSquared);
			vec2 targetFromCenter = fromCenter * (tan(half_pi * dist / radius / scale) * fisheyeFactor + (1.0 - fisheyeFactor));
			vec2 target = center + targetFromCenter;
			gl_FragColor = texture2DRect(source, target);
		}
		else {
			gl_FragColor = vec4(0, 0, 0, 0);
		}
	}
	);

	string vertexShader = GLSL120(
		void main() {
		gl_Position = ftransform();
	}
	);

	ofStringReplace(fragmentShader, ";", ";\n");
	ofStringReplace(vertexShader, ";", ";\n");

	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentShader);
	shader.setupShaderFromSource(GL_VERTEX_SHADER, vertexShader);
	shader.bindDefaults();
	shader.linkProgram();
}

void ofxFisheye::m_begin() {
	source.begin();
	ofClear(0, 0);
}

void ofxFisheye::m_end() {
	source.end();

	ofPushStyle();
	ofFill();
	if (fisheyeFactor == 0 && scale == 1.0) {
		ofSetColor(255);
		source.draw(0, 0);
	}
	else {
		ofVec2f center(source.getWidth() / 2, source.getHeight() / 2);
		float radius = center.length();
		//float radius = source.getWidth() / 2;

		shader.begin();
		shader.setUniformTexture("source", source.getTexture(), source.getId());
		shader.setUniform1f("radius", radius);
		shader.setUniform2f("center", center);
		shader.setUniform1f("fisheyeFactor", fisheyeFactor);
		shader.setUniform1f("scale", scale);
		ofDrawRectangle(0, 0, source.getWidth(), source.getHeight());
		shader.end();
	}
	ofPopStyle();
}

void ofxFisheye::m_sourceResizeIfChanged() {
	if (source.getWidth() != areaWidth || source.getHeight() != areaHeight) {
		source.allocate(areaWidth, areaHeight, GL_RGBA, 4);
	}
}

void ofxFisheye::makeSingletonIfDoesntExist() {
	if (singleton != nullptr) return;

	singleton = new ofxFisheye();
}

void ofxFisheye::begin() {
	makeSingletonIfDoesntExist();
	singleton->m_begin();
}

void ofxFisheye::setSize(int width, int height) {
    makeSingletonIfDoesntExist();
    singleton->areaWidth = width;
    singleton->areaHeight = height;
    singleton->m_sourceResizeIfChanged();
}

void ofxFisheye::setWidth(int width) {
    makeSingletonIfDoesntExist();
    singleton->areaWidth = width;
    singleton->m_sourceResizeIfChanged();
}

void ofxFisheye::setHeight(int height) {
    makeSingletonIfDoesntExist();
    singleton->areaHeight = height;
    singleton->m_sourceResizeIfChanged();
}

int ofxFisheye::getWidth() {
    makeSingletonIfDoesntExist();
    return singleton->areaWidth;
}

int ofxFisheye::getHeight() {
    makeSingletonIfDoesntExist();
    return singleton->areaWidth;
}

void ofxFisheye::end() {
	makeSingletonIfDoesntExist();
	singleton->m_end();
}

void ofxFisheye::setFisheyeFactor(float _fisheyeFactor) {
	makeSingletonIfDoesntExist();
	//singleton->fisheyeFactor = MIN(1.0, MAX(0, _fisheyeFactor));
	singleton->fisheyeFactor = _fisheyeFactor;
}

void ofxFisheye::setScale(float _scale) {
	makeSingletonIfDoesntExist();
	singleton->scale = _scale;
}

float ofxFisheye::getScale() {
	makeSingletonIfDoesntExist();
	return singleton->scale;
}

float ofxFisheye::getFisheyeFactor() {
	makeSingletonIfDoesntExist();
	return singleton->fisheyeFactor;
}
