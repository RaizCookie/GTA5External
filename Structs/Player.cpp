#include "Player.h"

float Player::readHealth(ProcessManager &procManager, unsigned long worldPtr){
    float health = 0;
    procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_ENTITY_HEALTH}), &health, sizeof(health));
    return health;
}

float Player::readMaxHealth(ProcessManager &procManager, unsigned long worldPtr){
    float maxHealth = 0;
    procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_ENTITY_HEALTH_MAX}), &maxHealth, sizeof(maxHealth));
    return maxHealth;
}

float Player::readArmor(ProcessManager &procManager, unsigned long worldPtr){
    float armor = 0;
    procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_PLAYER_ARMOR}), &armor, sizeof(armor));
    return armor;
}

bool Player::isGodmode(ProcessManager &procManager, unsigned long worldPtr){
    bool godmode = false;
    procManager.ReadProcessMemory((void*)procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_ENTITY_GOD}), &godmode, sizeof(godmode));
    return godmode;
}

bool Player::writeHealth(ProcessManager &procManager, unsigned long worldPtr, float health){
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER ,OFFSET_ENTITY_HEALTH}), &health, sizeof(health));
}

bool Player::writeArmor(ProcessManager &procManager, unsigned long worldPtr, float armor){
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_PLAYER_ARMOR}), &armor, sizeof(armor));
}

bool Player::writeWantedLevel(ProcessManager &procManager, unsigned long worldPtr, int wantedLevel) {
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_WANTED}), &wantedLevel, sizeof(wantedLevel));
}

bool Player::writeRunSpeed(ProcessManager &procManager, unsigned long worldPtr, float speed){
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_RUN_SPD}), &speed, sizeof(speed));
}

bool Player::writeSwimSpeed(ProcessManager &procManager, unsigned long worldPtr, float speed){
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_SWIM_SPD}), &speed, sizeof(speed));
}

bool Player::writeWantedCanChange(ProcessManager &procManager, unsigned long worldPtr, bool change){
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_WANTED_CAN_CHANGE}), &change, sizeof(change));
}

bool Player::writeNPCIgnore(ProcessManager &procManager, unsigned long worldPtr, int ignore){
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_NPC_IGNORE}), &ignore, sizeof(ignore));
}

bool Player::writeStamina(ProcessManager &procManager, unsigned long worldPtr, float stamina){
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_PLAYER_INFO_STAMINA}), &stamina, sizeof(stamina));
}

bool Player::writeRagdoll(ProcessManager &procManager, unsigned long worldPtr, char ragdoll){
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_PLAYER_RAGDOLL}), &ragdoll, sizeof(ragdoll));
}

bool Player::toggleGodmode(ProcessManager &procManager, unsigned long worldPtr){
    char godmode = 0x01;
    if(Player::isGodmode(procManager, worldPtr))
        godmode = 0x00;
    return procManager.WriteProcessMemory(procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_ENTITY_GOD}), &godmode, sizeof(godmode));
}

bool Player::writePosition(ProcessManager &procManager, unsigned long worldPtr, Vector3 coordinates){
    Player::writeRagdoll(procManager, worldPtr, 0x20);
    unsigned long posAddr = procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_ENTITY_POSBASE, OFFSET_ENTITY_POSBASE_POS});
    unsigned long posPedAddr = procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_ENTITY_POS});
    unsigned long posCarAddr = procManager.FindDMAAddy(worldPtr, {OFFSET_PLAYER, OFFSET_PLAYER_VEHICLE, OFFSET_ENTITY_POSBASE, OFFSET_ENTITY_POSBASE_POS});

    float currentCarX = 0;
    float currentPlayerX = 0;
    procManager.ReadProcessMemory((char*)posCarAddr, &currentCarX, sizeof(currentCarX));
    procManager.ReadProcessMemory((char*)posAddr, &currentPlayerX, sizeof(currentPlayerX));

    if (abs(currentCarX - currentPlayerX) < 1.0f)
		procManager.WriteProcessMemory(posCarAddr, &coordinates, sizeof(coordinates));
	
	procManager.WriteProcessMemory(posAddr, &coordinates, sizeof(coordinates));
	procManager.WriteProcessMemory(posPedAddr, &coordinates, sizeof(coordinates));

    return true;
}

