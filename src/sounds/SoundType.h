#ifndef SOUNDTYPE_H
#define SOUNDTYPE_H

#include "ChannelGroupID.h"

#include <fmod/fmod.h>
#include <string>

class SoundType {
public:
	std::string name;
	std::string path;
	ChannelGroupID channelGroupID;
	FMOD_MODE mode;
	float volume;
	float maxDistance;
};

#endif