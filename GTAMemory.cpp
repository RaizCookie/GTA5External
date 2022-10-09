#include "GTAMemory.h"

unsigned char GTAMemory::worldSignature[]  = { 0x48 ,0x8B ,0x05 ,0x00 ,0x00 ,0x00 ,0x00 ,0x45 ,0x00 ,0x00 ,0x00 ,0x00 ,0x48 ,0x8B ,0x48 ,0x08 ,0x48 ,0x85 ,0xC9 ,0x74 ,0x07 };
char GTAMemory::worldMask[] = "xxx????x????xxxxxxxxx";

unsigned long GTAMemory::scanWorldPtr(ProcessManager &procManager){

    unsigned long preWorld = procManager.ScanSignature(worldSignature, worldMask, 3);
    unsigned long worldPtr = 0xDEADBEEF;
    procManager.ReadProcessMemory((void*)(preWorld), &worldPtr, 4);
    return worldPtr + preWorld + 4;
}
