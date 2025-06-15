#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#include <string>

#include "../utils/Json.h"
#include "Sound.h"

class SoundSource {
public:
	std::string soundPrefix;

	std::shared_ptr<Sound> getSound(const std::string& suffix) const;
	bool containsSound(const std::string& suffix) const;
	void tryPlay3DSound(
		const std::string& suffix, const glm::vec3& position, const glm::vec3& velocity = glm::vec3(0), bool repeat = false) const;
	void tryPlaySound(const std::string& suffix, bool repeat = false) const;
	void loadSoundPrefix(const nlohmann::json& json);
};

#endif