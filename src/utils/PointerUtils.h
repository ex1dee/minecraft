#ifndef POINTERUTILS_H
#define POINTERUTILS_H

template<class T>
void freePointer(T** p) {
	if (*p != nullptr) {
		delete *p;
		p = nullptr;
	}
}

template<class T>
void freeArray(T& arr) {
	for (auto p : arr) {
		freePointer(&p);
	}

	arr.clear();
}

template<class T>
void freeMap(T& map) {
	for (auto p : map) {
		freePointer(&p.first);
		freePointer(&p.second);
	}

	map.clear();
}

template<class T>
void freeMapKeys(T& map) {
	for (auto p : map) {
		freePointer(&p.first);
	}

	map.clear();
}

template<class T>
void freeMapValues(T& map) {
	for (auto p : map) {
		freePointer(&p.second);
	}

	map.clear();
}

#endif