#pragma once
#include "../ProcessManager.h"
#include "../GTAMemory.h"
#include "Offsets.h"
class Player {
public:
    static float readHealth(ProcessManager &procManager, unsigned long worldPtr);
    static float readMaxHealth(ProcessManager &procManager, unsigned long worldPtr);	
    static float readArmor(ProcessManager &procManager, unsigned long worldPtr);

    static bool isGodmode(ProcessManager &procManager, unsigned long worldPtr);

    static bool writeHealth(ProcessManager &procManager, unsigned long worldPtr, float health);
    static bool writeArmor(ProcessManager &procManager, unsigned long worldPtr, float armor);

    static bool writeWantedLevel(ProcessManager &procManager, unsigned long worldPtr, int wantedLevel);

    static bool writeRunSpeed(ProcessManager &procManager, unsigned long worldPtr, float speed);

    static bool writeSwimSpeed(ProcessManager &procManager, unsigned long worldPtr, float speed);

    static bool writeWantedCanChange(ProcessManager &procManager, unsigned long worldPtr, bool change);
    static bool writeNPCIgnore(ProcessManager &procManager, unsigned long worldPtr, int ignore);

    static bool writeStamina(ProcessManager &procManager, unsigned long worldPtr, float stamina);

    static bool writeRagdoll(ProcessManager &procManager, unsigned long worldPtr, char ragdoll);

    static bool toggleGodmode(ProcessManager &procManager, unsigned long worldPtr);

    static bool writePosition(ProcessManager &procManager, unsigned long worldPtr, Vector3 coordinates);
    };