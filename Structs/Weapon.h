#pragma once
#include "../ProcessManager.h"
#include "../GTAMemory.h"
#include "Offsets.h"
class Weapon {
public:
    static float readDamage(ProcessManager procManager, unsigned long worldPtr);
    static float readRecoil(ProcessManager procManager, unsigned long worldPtr);
    static float readSpread(ProcessManager procManager, unsigned long worldPtr);
    static float readRange(ProcessManager procManager, unsigned long worldPtr);
    static float readReloadMultiplier(ProcessManager procManager, unsigned long worldPtr);

    static bool writeDamage(ProcessManager procManager, unsigned long worldPtr, float damage);
    static bool writeRecoil(ProcessManager procManager, unsigned long worldPtr, float recoil);
    static bool writeSpread(ProcessManager procManager, unsigned long worldPtr, float spread);
    static bool writeRange(ProcessManager procManager, unsigned long worldPtr, float range);
    static bool writeReloadMultiplier(ProcessManager procManager, unsigned long worldPtr, float multiplier);
};