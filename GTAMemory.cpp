#include "GTAMemory.h"

const char GTAMemory::worldSignature[]  = "\x48\x8B\x05\x00\x00\x00\x00\x45\x00\x00\x00\x00\x48\x8B\x48\x08\x48\x85\xC9\x74\x07";
char GTAMemory::worldMask[] = "xxx????x????xxxxxxxxx";

unsigned long GTAMemory::scanWorldPtr(ProcessManager &procManager){

    unsigned long preWorld = procManager.SignaturePayload(worldSignature, worldMask, nullptr, strlen(worldMask), 0, 8, 3);
    unsigned long worldPtr = 0xDEADBEEF;
    procManager.ReadProcessMemory((void*)(preWorld), &worldPtr, 4);
    return worldPtr + preWorld + 4;
}
