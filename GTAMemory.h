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
    static unsigned char worldSignature[];
    static char worldMask[];
public:
    static unsigned long scanWorldPtr(ProcessManager &procManager);

};