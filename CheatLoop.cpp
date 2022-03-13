#include "CheatLoop.h"

std::vector<std::string> split(std::string strToSplit, char splitChar){
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while(std::getline(ss, item, splitChar)){
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}

struct cmds {
    std::string name;
    void (CheatLoop::*func) (void *data);
};


void CheatLoop::getPointer(void *data) {
    Logger::log("INFO", "WorldPointer -> " + int_to_hex(pointer.at("world")), LogType::INFO);
    //Logger::log("INFO", "Blipptr -> " + std::to_string(pointer.at("coords")), LogType::INFO);
}
void CheatLoop::toggleGod(void *data) {
    god = !god;
    Logger::log("STATUS", "Godmode", LogType::STATUS, CheatLoop::god);
}
void CheatLoop::heal(void *data) {
    Player::writeArmor(procManager, pointer.at("world"), 100);
    Player::writeHealth(procManager, pointer.at("world"), Player::readMaxHealth(procManager, pointer.at("world")));
}
void CheatLoop::setWanted(void *data) {
    std::vector<std::string> arguments = *reinterpret_cast<std::vector<std::string>*>(data);
    Player::writeWantedLevel(procManager, pointer.at("world"), std::stoi(arguments.at(1)));
}
void CheatLoop::setRunSpeed(void *data) {
    std::vector<std::string> arguments = *reinterpret_cast<std::vector<std::string>*>(data);
    if(arguments.size() > 1)
        Player::writeRunSpeed(procManager, pointer.at("world"), std::stof(arguments.at(1)));
    else
        Logger::log("ERROR", "Too few arguments!", LogType::ERR);
}
void CheatLoop::setSwimSpeed(void *data) {
    std::vector<std::string> arguments = *reinterpret_cast<std::vector<std::string>*>(data);
    if(arguments.size() > 1)
        Player::writeSwimSpeed(procManager, pointer.at("world"), std::stof(arguments.at(1)));
    else
        Logger::log("ERROR", "Too few arguments!", LogType::ERR);
}
void CheatLoop::vHealth(void *data) {
    std::vector<std::string> arguments = *reinterpret_cast<std::vector<std::string>*>(data);
    Vehicle::writeHealth(procManager, procManager.FindDMAAddy(pointer.at("world"), {OFFSET_PLAYER, OFFSET_PLAYER_VEHICLE}), std::stof(arguments.at(1)));
    Vehicle::writeHealth2(procManager, procManager.FindDMAAddy(pointer.at("world"), {OFFSET_PLAYER, OFFSET_PLAYER_VEHICLE}), std::stof(arguments.at(1)));
}
void CheatLoop::setRagdoll(void *data) {
    std::vector<std::string> arguments = *reinterpret_cast<std::vector<std::string>*>(data);
    char mode = 0x00;
    if(arguments.at(1) == "0")
        mode = 0x20;
    Player::writeRagdoll(procManager, pointer.at("world"), mode);
}
void CheatLoop::setPosition(void *data) {
    std::vector<std::string> arguments = *reinterpret_cast<std::vector<std::string>*>(data);
    if(arguments.size() > 2) {
        Player::writePosition(procManager, pointer.at("world"), {std::stof(arguments.at(1)), std::stof(arguments.at(2)), stof(arguments.at(3))});
    }
    if(arguments.size() > 1) {
        Vector3 blipCoords = {0,0,0};
        procManager.ReadProcessMemory((void*)pointer.at("coords"), &blipCoords, sizeof(blipCoords));
        blipCoords.z = -210;
        Player::writePosition(procManager, pointer.at("world"), blipCoords);
    }
}
void CheatLoop::setLockOn(void *data) {
    Vehicle::toggleLockon(procManager, procManager.FindDMAAddy(pointer.at("world"), {OFFSET_PLAYER, OFFSET_PLAYER_VEHICLE}));
    Logger::log("STATUS", "AntiLockon:", LogType::STATUS, !Vehicle::readLockon(procManager, procManager.FindDMAAddy(pointer.at("world"), {OFFSET_PLAYER, OFFSET_PLAYER_VEHICLE})));
}

void CheatLoop::editWeaponMods(void *data) {
    std::vector<std::string> arguments = *reinterpret_cast<std::vector<std::string>*>(data);
    float damage = 1000;
    float range = 1000;
    float recoil = 0;
    float reloadMultiplier = 3;
    if(arguments.size() > 4) {
        damage = std::stof(arguments.at(1));
        range = std::stof(arguments.at(2));
        recoil = std::stof(arguments.at(3));
        reloadMultiplier = std::stof(arguments.at(4));
    }
    Weapon::writeDamage(procManager, pointer.at("world"), damage);
    Weapon::writeRange(procManager, pointer.at("world"), range);
    Weapon::writeRecoil(procManager, pointer.at("world"), recoil);
    Weapon::writeReloadMultiplier(procManager, pointer.at("world"), reloadMultiplier);
            
    Logger::log("WEAPON", "Weapon modified - damage -> " + std::to_string(damage) +
             " - range -> " + std::to_string(range) + " - recoil -> " + std::to_string(recoil) + 
             " - reloadMultiplier -> " + std::to_string(reloadMultiplier), LogType::PASSED);
}

void CheatLoop::speed(void *data) {
    float speed = Vehicle::readSpeed(procManager, procManager.FindDMAAddy(pointer.at("world"), {OFFSET_PLAYER, OFFSET_PLAYER_VEHICLE}));
    Logger::log("INFO", "Current speed: " + std::to_string(speed*3.6/*0.621*/)+ " kph", LogType::PASSED);
}

static cmds commands[] = {
    {"info", &CheatLoop::getPointer},
    {"god", &CheatLoop::toggleGod},
    {"full", &CheatLoop::heal},
    {"wanted", &CheatLoop::setWanted},
    {"ragdoll", &CheatLoop::setRagdoll},
    {"run", &CheatLoop::setRunSpeed},
    {"swim", &CheatLoop::setSwimSpeed},
    {"vhealth", &CheatLoop::vHealth},
    {"lockon", &CheatLoop::setLockOn},
    {"weapon", &CheatLoop::editWeaponMods},
    {"speed", &CheatLoop::speed},
};

CheatLoop::CheatLoop(ProcessManager &procManager, std::map<std::string, unsigned long> pointer) : procManager(procManager), pointer(pointer){}

void CheatLoop::startMainThread(std::vector<std::string> &arguments){

    while(arguments.at(0) != "exit") {
        if(god) {
            if(!Player::isGodmode(procManager, pointer.at("world")))
                Player::toggleGodmode(procManager, pointer.at("world"));
        } else {
            if(Player::isGodmode(procManager, pointer.at("world")))
                Player::toggleGodmode(procManager, pointer.at("world"));
        }

        bool commandExists = false;
        for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); ++i) {
            if (commands[i].name.compare(arguments.at(0)) == 0) {
                commandExists = true;
                void (CheatLoop::*cmd)(void* data) = commands[i].func;
                (this->*cmd)(&arguments);
            }
        }
        if(!arguments.at(0).empty() && !commandExists) {
            Logger::log("WARNING", "Command not found!", LogType::WARN);
        }
        
        arguments.clear();
        arguments.push_back("");
        usleep(50);
    }
}

bool CheatLoop::start(){
    std::string line = "";
    std::vector<std::string> arguments = {""};

    std::thread t1(&CheatLoop::startMainThread, this, std::ref(arguments));

    Logger::log("COMMAND", "", LogType::COMMAND);
    while(arguments.at(0) != "exit") {
        std::getline(std::cin, line);
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        arguments = split(line, ' ');
        usleep(100);
        if(arguments.at(0) != "exit")
            Logger::log("COMMAND", "", LogType::COMMAND);
    }

    t1.join();

    return true;
}
