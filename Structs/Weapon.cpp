#include "Weapon.h"

float Weapon::readDamage(ProcessManager procManager, unsigned long worldPtr) {
    float damage = 0;
    procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(worldPtr, 
    {   OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_BULLET_DMG   }
    ), &damage, sizeof(damage));
    return damage;
}
float Weapon::readRecoil(ProcessManager procManager, unsigned long worldPtr) {
    float recoil = 0;
    procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(worldPtr, 
    {   OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RECOIL   }
    ), &recoil, sizeof(recoil));
    return recoil;
}
float Weapon::readSpread(ProcessManager procManager, unsigned long worldPtr) {
    float spread = 0;
    procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(worldPtr, 
    {   OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_SPREAD   }
    ), &spread, sizeof(spread));
    return spread;
}
float Weapon::readRange(ProcessManager procManager, unsigned long worldPtr) {
    float range = 0;
    procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(worldPtr, 
    {   OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RANGE   }
    ), &range, sizeof(range));
    return range;
}
float Weapon::readReloadMultiplier(ProcessManager procManager, unsigned long worldPtr) {
    float multiplier = 0;
    procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(worldPtr, 
    {   OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RELOAD_MULTIPLIER   }
    ), &multiplier, sizeof(multiplier));
    return multiplier;
}

// Writing
bool Weapon::writeDamage(ProcessManager procManager, unsigned long worldPtr, float damage) {
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, 
    {   OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_BULLET_DMG   }
    ), &damage, sizeof(damage));
}
bool Weapon::writeRecoil(ProcessManager procManager, unsigned long worldPtr, float recoil) {
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, 
    {   OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RECOIL   }
    ), &recoil, sizeof(recoil));
}
bool Weapon::writeSpread(ProcessManager procManager, unsigned long worldPtr, float spread) {
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, 
    {   OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_SPREAD   }
    ), &spread, sizeof(spread));
}
bool Weapon::writeRange(ProcessManager procManager, unsigned long worldPtr, float range) {
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, 
    {   OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RANGE   }
    ), &range, sizeof(range));
}
bool Weapon::writeReloadMultiplier(ProcessManager procManager, unsigned long worldPtr, float multiplier) {
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, 
    {   OFFSET_PLAYER, OFFSET_WEAPON_MANAGER, OFFSET_WEAPON_CURRENT, OFFSET_WEAPON_RELOAD_MULTIPLIER   }
    ), &multiplier, sizeof(multiplier));
}