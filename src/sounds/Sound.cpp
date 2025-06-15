#include "Sound.h"

Sound::Sound(FMOD_SYSTEM* system,
    const std::string& path,
    const std::shared_ptr<ChannelGroup>& channelGroup,
    FMOD_MODE mode,
    float volume,
    float maxDistance
) : AudioResource(mode, volume), system(system), channelGroup(channelGroup), 
    handle(nullptr), channel(nullptr), maxDistance(maxDistance) {
    
    FMODHelper::checkError(FMOD_System_CreateStream(system, path.c_str(), mode, 0, &handle));
}

Sound::~Sound() {
    FMODHelper::checkError(FMOD_Channel_Stop(channel));
	FMODHelper::checkError(FMOD_Sound_Release(handle));
}

void Sound::play3D(const glm::vec3& position, const glm::vec3& velocity, bool repeat) {
    set3DAttributes(position, velocity);
    play(repeat);

    FMODHelper::checkError(FMOD_Channel_Set3DMinMaxDistance(channel, 0.0f, maxDistance));
}

void Sound::play(bool repeat) {
    setPaused(false);
    
    if (!repeat && isPlaying()) {
        return;
    }
    
    FMODHelper::checkError(FMOD_System_PlaySound(system, handle, channelGroup->handle, false, &channel));
    FMODHelper::checkError(FMOD_Channel_SetVolume(channel, volume));
    FMODHelper::checkError(FMOD_Channel_SetMode(channel, mode));
}

void Sound::setPaused(bool paused) {
    if (!isPlaying()) return;

    AudioResource::setPaused(paused);
    FMODHelper::checkError(FMOD_Channel_SetPaused(channel, paused));
}

void Sound::setMuted(bool muted) {
    if (!isPlaying()) return;

    AudioResource::setMuted(muted);
    FMODHelper::checkError(FMOD_Channel_SetMute(channel, muted));
}

void Sound::set3DAttributes(const glm::vec3& position, const glm::vec3& velocity) {
    if (!isPlaying()) return;
    
    w3DAttributes.update(position, velocity);
    FMODHelper::checkError(FMOD_Channel_Set3DAttributes(channel, &w3DAttributes.position, &w3DAttributes.velocity));
}

void Sound::stopLoop() {
    if (!isPlaying()) return;

    FMODHelper::checkError(FMOD_Channel_SetMode(channel, mode | FMOD_LOOP_OFF));
}

bool Sound::isPlaying() const {
    if (!channel) return false;

    FMOD_BOOL playing = false;
    FMOD_RESULT result = FMOD_Channel_IsPlaying(channel, &playing);

    return result == FMOD_OK && playing;
}