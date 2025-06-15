#include "SoundEngine.h"

#include "FMODHelper.h"

#include <fmod/fmod_errors.h>
#include <glm/glm.hpp>
#include <iostream>

constexpr float DOPPLER_EFFECT_FACTOR = 0.05f;

std::unordered_map<ChannelGroupID, std::shared_ptr<ChannelGroup>> SoundEngine::channelGroups;
std::unordered_map<std::string, std::shared_ptr<Sound>> SoundEngine::sounds;
W3DAttributes SoundEngine::listener3DAttributes;
FMOD_SYSTEM* SoundEngine::system;

void SoundEngine::initialize() {
    if (FMODHelper::checkError(FMOD_System_Create(&system, FMOD_VERSION)) != FMOD_OK) throw;
    if (FMODHelper::checkError(FMOD_System_Init(system, SE_MAX_CHANNELS, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0)) != FMOD_OK) throw;
}

void SoundEngine::finalize(void) {
    FMODHelper::checkError(FMOD_System_Release(system));
}

void SoundEngine::createChannelGroup(ChannelGroupID id, FMOD_MODE mode, float volume) {
    channelGroups.emplace(id, std::make_shared<ChannelGroup>(system, id, mode, volume));
}

void SoundEngine::loadSound(const std::string& name) {
    const SoundType& type = SoundsDatabase::get(name);

    if (!channelGroups.contains(type.channelGroupID)) {
        std::cerr << "Channel group with id " << type.channelGroupID << " not found\n";

        return;
    }

    sounds.emplace(type.name, std::make_shared<Sound>(
        system, type.path, channelGroups[type.channelGroupID], type.mode, type.volume, type.maxDistance
    ));
}

void SoundEngine::update(const std::shared_ptr<Player>& player) {
    setListener3DAttributes(player);

    FMODHelper::checkError(FMOD_System_Update(system));
}

void SoundEngine::setListener3DAttributes(const std::shared_ptr<Player>& player) {
    listener3DAttributes.update(
        player->transform.position,
        player->rigidBody.velocity * DOPPLER_EFFECT_FACTOR,
        player->orientation.getFront(),
        player->orientation.getUp()
    );

    FMODHelper::checkError(FMOD_System_Set3DListenerAttributes(
        system, 
        0, 
        &listener3DAttributes.position, 
        &listener3DAttributes.velocity, 
        &listener3DAttributes.forward, 
        &listener3DAttributes.up)
    );
}