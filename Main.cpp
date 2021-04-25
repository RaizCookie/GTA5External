
#include "ProcessManager.h"
#include "GTAMemory.h"
#include "CheatLoop.h"

int main(int argc, char *argv[])
{

    //TODO: Implement GUI? wxWidgets?
    //TODO: Cleanup and code refactoring
    //TODO: Gain information about blip pointer and possible signature


    ProcessManager procManager("GTA5.exe", "GTA5.exe");
    
    printf("%p\t ->\t %p\n", (void *)procManager.TargetBaseAddress, (void *)procManager.ModuleSize);
    printf("Scanning for Pointers...\n");

    std::map<std::string, unsigned long> pointer;
    pointer.insert(std::pair<std::string, unsigned long>("world", GTAMemory::scanWorldPtr(procManager)));
    pointer.insert(std::pair<std::string, unsigned long>("coords", 0x141faf560)); 

    CheatLoop cheatLoop(procManager, pointer);
    cheatLoop.start();

    procManager.~ProcessManager();
    
    return 0;
}
