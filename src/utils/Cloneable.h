#ifndef CLONEABLE_H
#define CLONEABLE_H

template<typename T>
class Cloneable {
public:
	virtual T* clone();
};

#endif