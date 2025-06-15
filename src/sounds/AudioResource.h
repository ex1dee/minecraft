#ifndef AUDIORESOURCE_H
#define AUDIORESOURCE_H

#include <fmod/fmod.h>
#include <glm/glm.hpp>

class AudioResource {
protected:
	FMOD_MODE mode;
	float volume;
	bool paused;
	bool muted;
public:
	AudioResource(FMOD_MODE mode, float volume) : mode(mode), paused(false), muted(false) { setVolume(volume); }

	float getVolume() { return volume; }
	bool isPaused() { return paused; }
	bool isMuted() { return muted; }

	virtual void setVolume(float volume) { this->volume = glm::clamp(volume, 0.0f, 1.0f); }
	virtual void setPaused(bool paused) { this->paused = paused; }
	virtual void setMode(FMOD_MODE mode) { this->mode = mode; }
	virtual void setMuted(bool muted) { this->muted = muted; }
};

#endif