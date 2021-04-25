#include "Vehicle.h"

    float Vehicle::readHealth(ProcessManager &procManager, unsigned long vehiclePtr){   return 0;}
    float Vehicle::readHealth2(ProcessManager &procManager, unsigned long vehiclePtr){return 0;}	
    bool Vehicle::readLockon(ProcessManager &procManager, unsigned long vehiclePtr){
        bool lockon = false;
        procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(vehiclePtr, {OFFSET_VEHICLE_LOCKON}), &lockon, sizeof(lockon));
        return lockon;
    }	

    float Vehicle::readAcceleration(ProcessManager &procManager, unsigned long vehiclePtr){
        float acceleration = false;
        procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(vehiclePtr, {OFFSET_VEHICLE_BOOST}), &acceleration, sizeof(acceleration));
        return acceleration;
    }

    bool Vehicle::writeHealth(ProcessManager &procManager, unsigned long vehiclePtr, float health){
        return procManager.WriteProcessMemory(procManager.FindDMAAddy(vehiclePtr, {OFFSET_VEHICLE_HEALTH}), &health, sizeof(health));

    }
    bool Vehicle::writeHealth2(ProcessManager &procManager, unsigned long vehiclePtr, float health){
        return procManager.WriteProcessMemory(procManager.FindDMAAddy(vehiclePtr, {OFFSET_VEHICLE_HEALTH2}), &health, sizeof(health));
    }
    bool Vehicle::toggleLockon(ProcessManager &procManager, unsigned long vehiclePtr){
        char lockon = 0x01;
        if(Vehicle::readLockon(procManager, vehiclePtr))
            lockon = 0x00;
        return procManager.WriteProcessMemory(procManager.FindDMAAddy(vehiclePtr, {OFFSET_VEHICLE_LOCKON}), &lockon, sizeof(lockon));
    }