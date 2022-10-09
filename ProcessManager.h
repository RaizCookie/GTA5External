#pragma once
#include "Utils/Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <istream>

#include <stdio.h>      // Input/Output
#include <stdlib.h>     // Standard Library
#include <string.h> 
#include <strings.h>    // String library
#include <unistd.h>     // Unix Standard
#include <sys/stat.h>   // Linux sys libs
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>      // Linux File Control API
#include <dirent.h>     // Linux Directory API
#include <errno.h>      // Error lib
#include <iostream>
#include <vector>


class ProcessManager {
private:
    char ProcessNameString[1024];
    long ProcessID = 0;
    int ProcessHandle = 0;

    long FindBaseAddress(const char *module = NULL);

public:
    unsigned long TargetBaseAddress = 0;
    unsigned long ModuleSize = 0;
    
    ProcessManager(const char *szProcessName, const char *module = NULL);
    ~ProcessManager();

    unsigned long ScanSignature(unsigned char signature[], const char *mask, unsigned long sigoffset = 0);
    ulong FindDMAAddy(ulong ptr, std::vector<unsigned int> offsets);
    bool WriteProcessMemory(unsigned long address, void *buffer, unsigned int size);

    bool ReadProcessMemory(void* address, void *buffer, unsigned int size);
};

