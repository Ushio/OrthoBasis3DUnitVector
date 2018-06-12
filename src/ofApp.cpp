#include "ofApp.h"

#define REVISITED 1

#if REVISITED == 0
// Building an Orthonormal Basis from a 3D Unit Vector Without Normalization
inline void orthonormalBasis(const glm::vec3& zaxis, glm::vec3 *xaxis, glm::vec3 *yaxis)
{
	// handle the singularity
	if (zaxis.z < -0.9999999f)
	{
		*xaxis = glm::vec3(0.0f, -1.0f, 0.0f);
		*yaxis = glm::vec3(-1.0f, 0.0f, 0.0f);
		return;
	}
	const float a = 1.0f / (1.0f + zaxis.z);
	const float b = -zaxis.x*zaxis.y * a;
	*xaxis = glm::vec3(1.0f - zaxis.x * zaxis.x * a, b, -zaxis.x);
	*yaxis = glm::vec3(b, 1.0f - zaxis.y * zaxis.y * a, -zaxis.y);
}

#else 
// Building an Orthonormal Basis, Revisited
inline void orthonormalBasis(const glm::vec3& zaxis, glm::vec3 *xaxis, glm::vec3 *yaxis) {
	float sign = copysignf(1.0f, zaxis.z);
	const float a = -1.0f / (sign + zaxis.z);
	const float b = zaxis.x * zaxis.y * a;
	*xaxis = glm::vec3(1.0f + sign * zaxis.x * zaxis.x * a, sign * b, -sign * zaxis.x);
	*yaxis = glm::vec3(b, sign + zaxis.y * zaxis.y * a, -zaxis.y);
}

#endif

inline glm::vec3 uniformOnUnitSphere(PeseudoRandom *random) {
	glm::vec3 d;
	float sq = 0.0f;
	do {
		d.x = random->uniformf(-1.0f, 1.0f);
		d.y = random->uniformf(-1.0f, 1.0f);
		d.z = random->uniformf(-1.0f, 1.0f);

		sq = glm::length2(d);
	} while (sq < 0.0001f || 1.0f < sq);
	d /= glm::sqrt(sq);
	return d;
}
//--------------------------------------------------------------
void ofApp::setup(){

	_camera.setNearClip(0.1f);
	_camera.setFarClip(100.0f);
	_camera.setDistance(5.0f);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	Xor64 random;

	ofEnableDepthTest();

	ofClear(0);
	_camera.begin();
	ofPushMatrix();
	ofRotateZ(90.0f);
	ofSetColor(128);
	ofDrawGridPlane(1.0f);
	ofPopMatrix();

	for (int i = 0; i < 10000; ++i) {
		glm::vec3 o(random.uniformf(-5.0f, 5.0f), random.uniformf(0.0f, 5.0f), random.uniformf(-5.0f, 5.0f));
		glm::vec3 zaxis = uniformOnUnitSphere(&random);

		// singularity test
		if (i % 1000 == 0) {
			zaxis = glm::vec3(0.0f, 0.0f, -1.0f);
		}

		glm::vec3 xaxis;
		glm::vec3 yaxis;
		orthonormalBasis(zaxis, &xaxis, &yaxis);

		ofSetColor(255, 0, 0);
		ofDrawLine(o, o + xaxis * 0.1f);

		ofSetColor(0, 255, 0);
		ofDrawLine(o, o + yaxis * 0.1f);

		ofSetColor(0, 0, 255);
		ofDrawLine(o, o + zaxis * 0.1f);

#if REVISITED
		// simple numerical test
		float a = glm::abs(glm::dot(xaxis, yaxis));
		if (1.0e-6f <= glm::abs(glm::dot(xaxis, yaxis))) {
			abort();
		}
		if (1.0e-6f <= glm::abs(glm::dot(yaxis, zaxis))) {
			abort();
		}
		if (1.0e-6f <= glm::abs(glm::dot(zaxis, xaxis))) {
			abort();
		}

		glm::vec3 maybe_zaxis = glm::cross(xaxis, yaxis);
		for (int j = 0; j < 3; ++j) {
			if (1.0e-6f <= glm::abs(zaxis[j] - maybe_zaxis[j])) {
				abort();
			}
		}
#else
		// simple numerical test
		float a = glm::abs(glm::dot(xaxis, yaxis));
		if (1.0e-4f <= glm::abs(glm::dot(xaxis, yaxis))) {
			abort();
		}
		if (1.0e-4f <= glm::abs(glm::dot(yaxis, zaxis))) {
			abort();
		}
		if (1.0e-4f <= glm::abs(glm::dot(zaxis, xaxis))) {
			abort();
		}

		glm::vec3 maybe_zaxis = glm::cross(xaxis, yaxis);
		for (int j = 0; j < 3; ++j) {
			if (1.0e-4f <= glm::abs(zaxis[j] - maybe_zaxis[j])) {
				abort();
			}
		}
#endif
	}

	_camera.end();

	ofDisableDepthTest();
	ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
