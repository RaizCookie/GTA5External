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

CheatLoop::CheatLoop(ProcessManager &procManager, std::map<std::string, unsigned long> pointer) : procManager(procManager), pointer(pointer){}

void CheatLoop::startMainThread(std::vector<std::string> &arguments){
    bool god = false;

    while(arguments.at(0) != "exit") {
        if(god) {
            if(!Player::isGodmode(procManager, pointer.at("world")))
                Player::toggleGodmode(procManager, pointer.at("world"));
        } else {
            if(Player::isGodmode(procManager, pointer.at("world")))
                Player::toggleGodmode(procManager, pointer.at("world"));
        }

        if(arguments.at(0) == "god"){
            god = !god;
            printf("Godmode %s\n", god ? "activated" : "deactivated");
       }
       else if(arguments.at(0) == "info") {
            printf("Worldptr: %lu\nBlipptr: %lu\n", pointer.at("world"), pointer.at("coords"));
       }
        else if(arguments.at(0) == "full"){
            Player::writeArmor(procManager, pointer.at("world"), 100);
            Player::writeHealth(procManager, pointer.at("world"), Player::readMaxHealth(procManager, pointer.at("world")));
        }
        else if(arguments.at(0) == "wanted"){
            Player::writeWantedLevel(procManager, pointer.at("world"), std::stoi(arguments.at(1)));
        }
        else if(arguments.at(0) == "run") {
            Player::writeRunSpeed(procManager, pointer.at("world"), std::stof(arguments.at(1)));
        }
        else if(arguments.at(0) == "ragdoll") {
            char mode = 0x00;
            if(arguments.at(1) == "0")
                mode = 0x20;
            Player::writeRagdoll(procManager, pointer.at("world"), mode);
        }
        else if(arguments.at(0) == "pos") {
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
        else if(arguments.at(0) == "vhealth") {
            Vehicle::writeHealth(procManager, procManager.FindDMAAddy(pointer.at("world"), {OFFSET_PLAYER, OFFSET_PLAYER_VEHICLE}), std::stof(arguments.at(1)));
            Vehicle::writeHealth2(procManager, procManager.FindDMAAddy(pointer.at("world"), {OFFSET_PLAYER, OFFSET_PLAYER_VEHICLE}), std::stof(arguments.at(1)));
        }
        else if(arguments.at(0) == "lockon") {
            Vehicle::toggleLockon(procManager, procManager.FindDMAAddy(pointer.at("world"), {OFFSET_PLAYER, OFFSET_PLAYER_VEHICLE}));
            printf("Lockon status: %s\n", Vehicle::readLockon(procManager, procManager.FindDMAAddy(pointer.at("world"), {OFFSET_PLAYER, OFFSET_PLAYER_VEHICLE})) ? "\033[1;31mtrue\033[0m" : "\033[1;32mfalse\033[0m"); // Testing purpose
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

    while(arguments.at(0) != "exit") {
        std::getline(std::cin, line);
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        arguments = split(line, ' ');
    }

    t1.join();

    return true;
}