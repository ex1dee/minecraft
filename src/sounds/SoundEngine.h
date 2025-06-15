#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include "../player/Player.h"
#include "SoundsDatabase.h"
#include "SoundConstants.h"
#include "ChannelGroup.h"
#include "Sound.h"

#include <unordered_map>

class SoundEngine {
    static std::unordered_map<ChannelGroupID, std::shared_ptr<ChannelGroup>> channelGroups;
    static std::unordered_map<std::string, std::shared_ptr<Sound>> sounds;
    static W3DAttributes listener3DAttributes;
    static FMOD_SYSTEM* system;

    static void setListener3DAttributes(const std::shared_ptr<Player>& player);
public:
    static void initialize();
    static void finalize();

    static void loadSound(const std::string& name);
    static void update(const std::shared_ptr<Player>& player);
    static void createChannelGroup(ChannelGroupID id, FMOD_MODE mode, float volume = SE_DEFAULT_VOLUME);
    
    static std::shared_ptr<Sound> getSound(const std::string& name) { return sounds[name]; }
    static bool containsSound(const std::string& name) { return sounds.contains(name); }
};

#endif