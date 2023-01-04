#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetColor(0);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int span = 60;
	for (int x = -300; x <= 300; x += span) {

		for (int y = -300; y <= 300; y += span) {

			auto noise_value = ofNoise(x * 0.005, y * 0.005, ofGetFrameNum() * 0.01);
			auto next_noise_value = ofNoise(x * 0.005, y * 0.005, (ofGetFrameNum() + 1) * 0.01);
			
			auto noise_param = noise_value < 0.75 ? 0 : ofMap(noise_value, 0.75, 1, 0, 1);
			auto next_noise_param = next_noise_value < 0.75 ? 0 : ofMap(next_noise_value, 0.75, 1, 0, 1);

			auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

			auto param_x = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.05), 0, 1, span * -1.5, span * 1.5) * noise_param;
			auto param_y = ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.05), 0, 1, span * -1.5, span * 1.5) * noise_param;

			auto next_param_x = ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + 1) * 0.05), 0, 1, span * -1.5, span * 1.5) * next_noise_param;
			auto next_param_y = ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + 1) * 0.05), 0, 1, span * -1.5, span * 1.5) * next_noise_param;

			if (noise_param > 0) {

				this->draw_arrow(glm::vec2(x + param_x, y + param_y), glm::vec2(x + next_param_x, y + next_param_y), span * 0.25, ofColor(0));

				ofDrawLine(glm::vec2(x + param_x, y + param_y), glm::vec2(x + next_param_x, y + next_param_y));
			}
			else {

				ofFill();
				ofDrawCircle(x + param_x, y + param_y, span * 0.1);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 next_location, float size, ofColor color) {

	auto angle = std::atan2(next_location.y - location.y, next_location.x - location.x);

	ofSetColor(color);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.8 * cos(angle), size * 0.8 * sin(angle)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) + location);
	ofEndShape(true);

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape(true);

	ofSetColor(color);
	ofNoFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.8 * cos(angle), size * 0.8 * sin(angle)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5 + location);
	ofVertex(glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 + location);
	ofEndShape();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}