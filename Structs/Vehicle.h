#pragma once
#include "../ProcessManager.h"
#include "../GTAMemory.h"
#include "Offsets.h"
#include <math.h>

class Vehicle {
public:
    static float readHealth(ProcessManager &procManager, unsigned long vehiclePtr);
    static float readHealth2(ProcessManager &procManager, unsigned long vehiclePtr);	
    static bool readLockon(ProcessManager &procManager, unsigned long vehiclePtr);
    static float readAcceleration(ProcessManager &procManager, unsigned long vehiclePtr);
    static float readSpeed(ProcessManager &procManager, unsigned long vehiclePtr);

    static bool writeHealth(ProcessManager &procManager, unsigned long vehiclePtr, float health);
    static bool writeHealth2(ProcessManager &procManager, unsigned long vehiclePtr, float health);	
    static bool toggleLockon(ProcessManager &procManager, unsigned long vehiclePtr);
};