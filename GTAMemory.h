#pragma once
#include "ProcessManager.h"

struct Vector3{
	float x, y, z;
	Vector3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
};

class GTAMemory {
private:
    static const char worldSignature[];
	static const char blipSignature[];
    static char worldMask[];
	static char blipMask[];
public:
    static unsigned long scanWorldPtr(ProcessManager &procManager);

};