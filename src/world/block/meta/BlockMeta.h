#ifndef BLOCKMETA_H
#define BLOCKMETA_H

class BlockMeta {
public:
	virtual BlockMeta* clone() const {
		return new BlockMeta(*this);
	}
};

enum class BlockMetaID {
	LIQUID = 0
};

#endif