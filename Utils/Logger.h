#pragma once
#include "stdio.h"
#include <iostream>
#include <string>
#include <iomanip>

enum class LogType {
#ifdef _WIN32
	NORMAL = 15,
	INFO = 11,
	WARN = 14,
	ERR = 12,
	PASSED = 10,
	UNEXPECTED = 13
#else
	NORMAL = 37,
	INFO = 34,
    COMMAND = 35,
	WARN = 33,
	ERR = 31,
	PASSED = 32,
    STATUS = 36
#endif

};

template< typename T >
        std::string int_to_hex( T i ) {
            std::stringstream stream;
            stream << "0x" << std::setfill ('0') << std::setw(sizeof(T)*2) << std::hex << i;
            return stream.str();
            }

class Logger {
    public:
        static void log(std::string from, std::string message, LogType type, bool stat = false);
        
};