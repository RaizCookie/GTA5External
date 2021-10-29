#include "Logger.h"

void Logger::log(std::string from, std::string message, LogType type, bool stat) {
    
    if(type == LogType::COMMAND) {
         std::cout << "\033[1;" << static_cast<int>(type) << "m[" << from << "]\033[0m "; 
    }
    else if(type == LogType::STATUS) {
        std::cout << "\033[1;" << static_cast<int>(type) << "m[" << from << "]\033[0m " << message << " \033[1;" << (stat ? "32mtrue" : "31mfalse") << "\033[0m\n";
    }
    else {
        std::cout << "\033[1;" << static_cast<int>(type) << "m[" << from << "]\033[0m " << message << std::endl;
    }
    
}