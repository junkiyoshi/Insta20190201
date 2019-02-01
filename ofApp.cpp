#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(255);

    this->font.loadFont("fonts/Kazesawa-Bold.ttf", 280, true, true, true);
	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	for (int i = 0; i < ofGetHeight(); i++)	{ this->y_noise.push_back(glm::vec3()); }

	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {

	this->fbo.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofRotate(ofGetFrameNum());

	string word = "777";
	font.drawString(word, font.stringWidth(word) * -0.5, font.stringHeight(word) * 0.5);

	this->fbo.end();

	ofSeedRandom(39);
	glm::vec3 noise_value;
	glm::vec3 noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int y = 0; y < this->y_noise.size(); y++) {

		if (y % 8 == 0) {

			for (int i = 0; i < 3; i++) {

				noise_value[i] = ofMap(ofNoise(noise_seed[i], y * 0.03, ofGetFrameNum() * 0.02), 0, 1, -1, 1);

				if (noise_value[i] > 0.5) {

					noise_value[i] -= 0.5;
				}
				else if (noise_value[i] < -0.5) {

					noise_value[i] += 0.5;
				}
				else {

					noise_value[i] = 0.0;
				}
			}
		}

		this->y_noise[y] = noise_value;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex", this->fbo.getTexture(), 1);
	this->shader.setUniform3fv("y_noise", &this->y_noise[0].x, ofGetHeight());

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();

	ofImage image;
	image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	image.saveImage(to_string(ofGetFrameNum()) + ".png");
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}