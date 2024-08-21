#include "BlockMetaLoader.h"

std::unique_ptr<BlockMeta> BlockMetaLoader::load(BlockMetaID id, const nlohmann::basic_json<>& json) {
	nlohmann::basic_json<> meta = json["meta"];

	switch (id) {
	case BlockMetaID::LIQUID:
		return std::make_unique<Liquid>(meta["viscosity"], Json::toVec4(meta["fog_color"]), meta["fog_density"]);
	}
}