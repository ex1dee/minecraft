#ifndef CHANNELGROUP_H
#define CHANNELGROUP_H

#include "FMODHelper.h"
#include "AudioResource.h"
#include "ChannelGroupID.h"

#include <string>

class Sound;

class ChannelGroup : public AudioResource {
	friend Sound;

	FMOD_CHANNELGROUP* handle;
	ChannelGroupID id;
public:
	ChannelGroup(FMOD_SYSTEM* system, ChannelGroupID id, FMOD_MODE mode, float volume);
	~ChannelGroup();

	void setPaused(bool paused) override;
	void setVolume(float volume) override;
	void setMode(FMOD_MODE mode) override;
	void setMuted(bool muted) override;
};

#endif