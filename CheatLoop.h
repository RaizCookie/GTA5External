#pragma once
#include "ProcessManager.h"
#include "GTAMemory.h"
#include "Structs/Player.h"
#include "Structs/Vehicle.h"
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
    private:
        ProcessManager procManager;
        std::map<std::string, unsigned long> pointer;
        void startMainThread(std::vector<std::string> &arguments);
        void startCommandThread();
};