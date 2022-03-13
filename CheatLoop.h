#pragma once
#include "ProcessManager.h"
#include "GTAMemory.h"
#include "Structs/Player.h"
#include "Structs/Vehicle.h"
#include "Structs/Weapon.h"
#include "Utils/Logger.h"
#include <thread>
#include <functional>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <map>

class CheatLoop {
    public:
        CheatLoop(ProcessManager &procManager, std::map<std::string, unsigned long> pointer);
        bool start();
        bool god = false;
        void getPointer(void *data);
        void toggleGod(void *data);
        void heal(void *data);
        void setWanted(void *data);
        void vHealth(void *data);
        void setRagdoll(void *data);
        void setRunSpeed(void *data);
        void setSwimSpeed(void *data);
        void setPosition(void *data);
        void setLockOn(void *data);
        void editWeaponMods(void *data);
        void speed(void *data);
    private:
        ProcessManager procManager;
        std::map<std::string, unsigned long> pointer;
        void startMainThread(std::vector<std::string> &arguments);
        void startCommandThread();
};