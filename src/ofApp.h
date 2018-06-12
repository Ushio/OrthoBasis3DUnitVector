#pragma once

#include "ofMain.h"

struct PeseudoRandom {
	virtual ~PeseudoRandom() {}

	// 0.0 <= x < 1.0
	virtual double uniform64f() = 0;
	virtual float uniform32f() = 0;

	// 0.0 <= x < 1.0
	double uniform() {
		return uniform64f();
	}
	// a <= x < b
	double uniform(double a, double b) {
		return glm::mix(a, b, uniform64f());
	}
	// 0.0 <= x < 1.0
	double uniformf() {
		return uniform32f();
	}
	// a <= x < b
	float uniformf(float a, float b) {
		return glm::mix(a, b, uniform32f());
	}
};

// copy and paste from:
//     https://ja.wikipedia.org/wiki/Xorshift 
struct Xor64 : public PeseudoRandom {
	Xor64() {

	}
	Xor64(uint64_t seed) {
		_x = std::max(seed, 1ULL);
	}
	uint64_t generate() {
		_x = _x ^ (_x << 7);
		_x = _x ^ (_x >> 9);
		return _x;
	}

	// copy and paste from:
	//     http://xoshiro.di.unimi.it/
	// より直観的な説明
	//     http://marupeke296.com/TIPS_No16_flaotrandom.html
	double uniform64f() override {
		uint64_t x = generate();
		uint64_t bits = (0x3FFULL << 52) | (x >> 12);
		double value = *reinterpret_cast<double *>(&bits) - 1.0;
		return value;
	}
	float uniform32f() override {
		uint64_t x = generate();
		uint32_t bits = ((uint32_t)x >> 9) | 0x3f800000;
		float value = *reinterpret_cast<float *>(&bits) - 1.0f;
		return value;
	}
	uint64_t _x = 88172645463325252ULL;
};

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofEasyCam _camera;
};
