#ifndef SOUNDSDATABASE_H
#define SOUNDSDATABASE_H

#include "SoundConstants.h"
#include "FMODHelper.h"
#include "SoundType.h"

#include <unordered_map>
#include <memory>

class SoundsDatabase {
	static std::unordered_map<std::string, std::unique_ptr<SoundType>> sounds;

	static std::string getSoundNameByPath(const std::string& path);
public:
	static void initialize();

	static const SoundType& get(const std::string& name) { return *sounds[name]; }
};

#endif