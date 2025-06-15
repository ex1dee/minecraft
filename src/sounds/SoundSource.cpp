#include "SoundSource.h"

#include "SoundEngine.h"

void SoundSource::tryPlay3DSound(
	const std::string& suffix, const glm::vec3& position, const glm::vec3& velocity, bool repeat) const {
	if (containsSound(suffix)) getSound(suffix)->play3D(position, velocity, repeat);
}

void SoundSource::tryPlaySound(const std::string& suffix, bool repeat) const {
	if (containsSound(suffix)) getSound(suffix)->play(repeat);
}

bool SoundSource::containsSound(const std::string& suffix) const {
	return SoundEngine::containsSound(soundPrefix + "." + suffix);
}

std::shared_ptr<Sound> SoundSource::getSound(const std::string& suffix) const {
	return SoundEngine::getSound(soundPrefix + "." + suffix);
}

void SoundSource::loadSoundPrefix(const nlohmann::json& json) {
	if (json.contains("soundPrefix"))
		soundPrefix = json["soundPrefix"];
}