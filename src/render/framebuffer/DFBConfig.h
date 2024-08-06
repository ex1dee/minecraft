#ifndef DFBConfig_H
#define DFBConfig_H

struct DFBConfig {
	float bufferSize;
	bool isOrtho;

	float perspectiveNear;
	float perspectiveFar;

	float orthoNear;
	float orthoFar;
	float orthoSize;

	DFBConfig() {}

	DFBConfig(float orthoNear, float orthoFar, float orthoSize, float bufferSize)
		: orthoNear(orthoNear), orthoFar(orthoFar), 
		  orthoSize(orthoSize), bufferSize(bufferSize) {
		isOrtho = true;
	}

	DFBConfig(float perspectiveNear, float perspectiveFar, float bufferSize)
		: bufferSize(bufferSize), perspectiveNear(perspectiveNear), perspectiveFar(perspectiveFar) {
		isOrtho = false;
	}
};

const DFBConfig DEFAULT_DFB { 0.1f, 100.0f, 50.0f, 1024.0f };

#endif