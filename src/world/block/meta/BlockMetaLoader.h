#ifndef BLOCKMETALOADER_H
#define BLOCKMETALOADER_H

#include "../../../utils/Json.h"
#include "Liquid.h"

class BlockMetaLoader {
public:
	static BlockMeta* load(BlockMetaID id, const nlohmann::basic_json<>& json);
};

#endif