#ifndef SOUND_H
#define SOUND_H

#include "FMODHelper.h"
#include "ChannelGroup.h"
#include "AudioResource.h"
#include "W3DAttributes.h"

#include <string>
#include <memory>

class Sound : public AudioResource {
	std::shared_ptr<ChannelGroup> channelGroup;
	W3DAttributes w3DAttributes;
	FMOD_CHANNEL* channel;
	FMOD_SYSTEM* system;
	FMOD_SOUND* handle;
	float maxDistance;
public:
	Sound(
		FMOD_SYSTEM* system, 
		const std::string& path,
		const std::shared_ptr<ChannelGroup>& channelGroup, 
		FMOD_MODE mode, 
		float volume,
		float maxDistance);
	~Sound();

	void stopLoop();
	void play(bool repeat = false);
	void play3D(const glm::vec3& position, const glm::vec3& velocity = glm::vec3(0.0f), bool repeat = false);
	void set3DAttributes(const glm::vec3& position, const glm::vec3& velocity = glm::vec3(0.0f));

	bool isPlaying() const;
	void setPaused(bool paused) override;
	void setMuted(bool muted) override;
};

#endif