#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 2);
	this->triangles = ico_sphere.getMesh().getUniqueFaces();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.8);
	ofRotateX(ofGetFrameNum() * 0.3);

	auto threshold = 0.65f;
	for (auto& triangle : this->triangles) {

		auto base_location_a = glm::vec3(triangle.getVertex(0).x, triangle.getVertex(0).y, triangle.getVertex(0).z);
		auto base_location_b = glm::vec3(triangle.getVertex(1).x, triangle.getVertex(1).y, triangle.getVertex(1).z);
		auto base_location_c = glm::vec3(triangle.getVertex(2).x, triangle.getVertex(2).y, triangle.getVertex(2).z);
		auto base_avg = (base_location_a + base_location_b + base_location_c) / 3;

		// 隣接する図形同士で重なる部分が出てくるので調整値の分だけ縮める
		base_location_a = (base_location_a - base_avg) * 0.95 + base_avg;
		base_location_b = (base_location_b - base_avg) * 0.95 + base_avg;
		base_location_c = (base_location_c - base_avg) * 0.95 + base_avg;

		auto noise_value = ofNoise(base_avg.x * 0.005, base_avg.y * 0.005, base_avg.z * 0.005, ofGetFrameNum() * 0.0025);
		if (noise_value >= threshold) {

			auto tmp_location_a = glm::normalize(base_location_a) * ofMap(noise_value, threshold, 1.0, 300, 450);
			auto tmp_location_b = glm::normalize(base_location_b) * ofMap(noise_value, threshold, 1.0, 300, 450);
			auto tmp_location_c = glm::normalize(base_location_c) * ofMap(noise_value, threshold, 1.0, 300, 450);
			
			ofFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertex(tmp_location_a);
			ofVertex(tmp_location_b);
			ofVertex(tmp_location_c);
			ofEndShape(true);

			ofBeginShape();
			ofVertex(base_location_a);
			ofVertex(base_location_b);
			ofVertex(tmp_location_b);
			ofVertex(tmp_location_a);
			ofEndShape(true);

			ofBeginShape();
			ofVertex(base_location_b);
			ofVertex(base_location_c);
			ofVertex(tmp_location_c);
			ofVertex(tmp_location_b);
			ofEndShape(true);

			ofBeginShape();
			ofVertex(base_location_c);
			ofVertex(base_location_a);
			ofVertex(tmp_location_a);
			ofVertex(tmp_location_c);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			ofVertex(tmp_location_a);
			ofVertex(tmp_location_b);
			ofVertex(tmp_location_c);
			ofEndShape(true);

			ofBeginShape();
			ofVertex(base_location_a);
			ofVertex(base_location_b);
			ofVertex(tmp_location_b);
			ofVertex(tmp_location_a);
			ofEndShape(true);

			ofBeginShape();
			ofVertex(base_location_b);
			ofVertex(base_location_c);
			ofVertex(tmp_location_c);
			ofVertex(tmp_location_b);
			ofEndShape(true);

			ofBeginShape();
			ofVertex(base_location_c);
			ofVertex(base_location_a);
			ofVertex(tmp_location_a);
			ofVertex(tmp_location_c);
			ofEndShape(true);
		}
		else {

			ofFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertex(base_location_a);
			ofVertex(base_location_b);
			ofVertex(base_location_c);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			ofVertex(base_location_a);
			ofVertex(base_location_b);
			ofVertex(base_location_c);
			ofEndShape(true);
		}
	}
	
	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}