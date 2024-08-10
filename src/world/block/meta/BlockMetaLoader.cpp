#include "BlockMetaLoader.h"

BlockMeta* BlockMetaLoader::load(BlockMetaID id, const nlohmann::basic_json<>& json) {
	switch (id) {
	case BlockMetaID::LIQUID:
		return new Liquid(json["meta"]["viscosity"]);
	}
}