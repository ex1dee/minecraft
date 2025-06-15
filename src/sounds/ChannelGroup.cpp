#include "ChannelGroup.h"

ChannelGroup::ChannelGroup(FMOD_SYSTEM* system, ChannelGroupID id, FMOD_MODE mode, float volume)
    : AudioResource(mode, volume), id(id), handle(nullptr) {

    FMODHelper::checkError(FMOD_System_CreateChannelGroup(system, std::to_string(id).c_str(), &handle));
    setVolume(volume);
    setMode(mode);
}

ChannelGroup::~ChannelGroup() {
    FMODHelper::checkError(FMOD_ChannelGroup_Release(handle));
}

void ChannelGroup::setPaused(bool paused) {
    AudioResource::setPaused(paused);
    FMODHelper::checkError(FMOD_ChannelGroup_SetPaused(handle, paused));
}

void ChannelGroup::setVolume(float volume) {
    AudioResource::setVolume(volume);
    FMODHelper::checkError(FMOD_ChannelGroup_SetVolume(handle, volume));
}

void ChannelGroup::setMode(FMOD_MODE mode) {
    AudioResource::setMode(mode);
    FMODHelper::checkError(FMOD_ChannelGroup_SetMode(handle, mode));
}

void ChannelGroup::setMuted(bool muted) {
    AudioResource::setMuted(muted);
    FMODHelper::checkError(FMOD_ChannelGroup_SetMute(handle, muted));
}