
#include "ProcessManager.h"
#include "GTAMemory.h"
#include "CheatLoop.h"

int main(int argc, char *argv[])
{

    //TODO: Implement GUI? wxWidgets?
    //TODO: Cleanup and code refactoring
    //TODO: Gain information about blip pointer and possible signature
    //TODO: CMake? Make file?

    ProcessManager procManager("GTA5.exe", "GTA5.exe");
    
    Logger::log("INFO", "Module Range: " + int_to_hex(procManager.TargetBaseAddress) + " -> " + int_to_hex(procManager.ModuleSize), LogType::INFO);
    Logger::log("INFO", "Scanning for Pointers...", LogType::INFO);

    std::map<std::string, unsigned long> pointer;
    pointer.insert(std::pair<std::string, unsigned long>("world", GTAMemory::scanWorldPtr(procManager)));
    pointer.insert(std::pair<std::string, unsigned long>("coords", GTAMemory::scanBlipPtr(procManager))); // Not working?

    CheatLoop cheatLoop(procManager, pointer);
    cheatLoop.start();

    procManager.~ProcessManager();
    
    return 0;
}
