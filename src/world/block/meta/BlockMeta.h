#ifndef BLOCKMETA_H
#define BLOCKMETA_H

class BlockMeta {
public:
	virtual ~BlockMeta() = default;
};

enum class BlockMetaID {
	LIQUID = 0
};

#endif