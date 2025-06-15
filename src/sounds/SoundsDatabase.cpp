#include "SoundsDatabase.h"

#include "../utils/Json.h"
#include "SoundEngine.h"

const char* SOUNDS_DIR = "resources/sounds/";
const char* SOUND_EXTENSION = ".ogg";

std::unordered_map<std::string, FMOD_MODE> SOUND_MODES = {
	{ "3D", FMOD_3D | FMOD_3D_LINEARSQUAREROLLOFF },
	{ "2D", FMOD_2D }
};

std::unordered_map<std::string, ChannelGroupID> CHANNEL_GROUP_IDS = {
	{ "blocks", ChannelGroupID::BLOCKS },
	{ "ambient", ChannelGroupID::AMBIENT }
};

std::unordered_map<std::string, std::unique_ptr<SoundType>> SoundsDatabase::sounds;

void SoundsDatabase::initialize() {
	for (const std::string& channelGroupDir : Files::getFolderFiles(SOUNDS_DIR, true)) {
		std::string channelGroupName = Files::getLastPathSegment(channelGroupDir);

		if (!CHANNEL_GROUP_IDS.contains(channelGroupName))
			continue;

		ChannelGroupID channelGroupID = CHANNEL_GROUP_IDS[channelGroupName];
		SoundEngine::createChannelGroup(channelGroupID, FMOD_DEFAULT);

		for (const std::string& path : Files::getFolderFilesDeep(channelGroupDir, false, "json")) {
			std::unique_ptr<SoundType> type = std::make_unique<SoundType>();
			nlohmann::json json = Json::parse(path);
			
			std::string name = getSoundNameByPath(path);
			type->name = name;
			type->channelGroupID = channelGroupID;
			type->path = Files::getPathBeforeExtension(path) + SOUND_EXTENSION;
			type->volume = json["volume"];
			type->mode = SOUND_MODES[json["mode"]];
			type->maxDistance = json["maxDistance"];

			sounds.emplace(type->name, std::move(type));
			SoundEngine::loadSound(name);
		}
	}
};

std::string SoundsDatabase::getSoundNameByPath(const std::string& fullPath) {
	std::string path = Files::getPathSegmentAfter(fullPath, SOUNDS_DIR);
	path = path.substr(0, path.find_last_of('.'));

	std::string buf = "";

	for (char c : path) {
		if (c == '/' or c == '\\')
			buf += '.';
		else
			buf += c;
	}

	return buf;
}