#ifndef DFBConfig_H
#define DFBConfig_H

struct DFBConfig {
	float buffer_size;
	bool is_ortho;

	float perspective_near;
	float perspective_far;

	float ortho_near;
	float ortho_far;
	float ortho_size;

	DFBConfig() {}

	DFBConfig(float ortho_near, float ortho_far, float ortho_size, float buffer_size)
		: ortho_near(ortho_near), ortho_far(ortho_far), 
		  ortho_size(ortho_size), buffer_size(buffer_size) {
		is_ortho = true;
	}

	DFBConfig(float buffer_size, float perspective_near, float perspective_far)
		: buffer_size(buffer_size), perspective_near(perspective_near), perspective_far(perspective_far) {
		is_ortho = false;
	}
};

const DFBConfig DEFAULT_DFB { 0.1f, 100.0f, 50.0f, 1024.0f };

#endif