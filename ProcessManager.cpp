#include "ProcessManager.h"

// Find base address of memory to start searching for signature
//
// Default base address will be the first executable region

long ProcessManager::FindBaseAddress(const char *module) {
    int fd = 0;
    char FileLocation[1024]; // File location to read memory modules
    char BaseAddress[1024];
    char LastAddress[1024];
    char *ptr = NULL;

    sprintf(FileLocation, "/proc/%lu/maps", ProcessID);

    // Open file and creating FileDescriptor
    if ((fd = open(FileLocation, O_RDONLY)) < 0) {
        fprintf(stderr, "[ERROR] ProcessManager: Failed to find process base address\n");
        return false;
    }

    // Create buffer for file
    char *FileBuffer = (char *)malloc(1000000);
    if (FileBuffer == NULL) {
        fprintf(stderr, "[ERROR] ProcessManager: Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    memset(FileBuffer, 0, 1000000);
    memset(BaseAddress, 0, 1024);
    memset(LastAddress, 0, 1024);
    

    // Read file into buffer
    for (int i = 0; read(fd, FileBuffer + i, 1) > 0; i++)
        ;

    // Close file
    close(fd);

    // Locate Base address
    if (module != NULL) {
        if ((ptr = strstr(FileBuffer, module)) == NULL) {
            fprintf(stderr, "[ERROR] ProcessManager: Failed to locate base memory address; NON\n");
            return false;
        }
    }
    else {
        if ((ptr = strstr(FileBuffer, "r-xp")) == NULL) {
            fprintf(stderr, "[ERROR] ProcessManager: Failed to locate base memory address\n");
            return false;
        }
    }

    // Copy address
    while (*ptr != '\n' && ptr >= FileBuffer) {
        ptr--; //Runter bis Ende vorheriger Zeile
    }
    ptr++; // Zurück zum Anfang der nächsten Zeile
    
    for (int i = 0; *ptr != '-'; i++) {
        BaseAddress[i] = *ptr;
        ptr++;
    }
    if (module != NULL) {
        char sizeString[1024];
        if (sizeString == NULL) {
            fprintf(stderr, "[ERROR] ProcessManager: Failed to allocate memory\n");
            exit(EXIT_FAILURE);
        }
        memset(sizeString, 0, 1024);
        for(int i = 0; i < 1024; i++) {
            sizeString[i] = *ptr;
            ptr++;
        }
        ptr++;
        for (int i = 0; *ptr != ' '; i++) {
                LastAddress[i] = *ptr;
                ptr++;
            }
            
        while (*ptr != '\n' && ptr >= sizeString)
            ptr++; 
            
        while((ptr = strstr(sizeString, module)) != NULL){
            memset(LastAddress, 0, 1024);
            while (*ptr != '\n' && ptr >= sizeString)
                ptr--; 
            ptr++;
            for (int i = 0; *ptr != '-'; i++)
                ptr++;
            ptr++;
            for (int i = 0; *ptr != ' '; i++) {
                LastAddress[i] = *ptr;
                ptr++;
            }
            
            while (*ptr != '\n' && ptr >= sizeString)
                ptr++; 
                
            ptr++;
            for(int i = 0; i < 1024; i++){
                sizeString[i] = *ptr;
                ptr++;
            } 
        }
        delete(ptr);
        ModuleSize = strtol(LastAddress, NULL, 16);
    } else {
        ModuleSize = 0x0;
    } 
    delete(FileBuffer);
    // Copy over address to public
    return strtol(BaseAddress, NULL, 16);
}

// Function will automatically search for signature and write payload

unsigned long ProcessManager::SignaturePayload(const char *signature, const char *mask, char *payload, const int siglen, const int paylen, const int bsize, unsigned long sigoffset) {
    
    unsigned long addr = 0xDEADBEEF;
    
    char *buf = (char *)malloc(siglen * bsize);
    if (buf == NULL) {
        fprintf(stderr, "[ERROR] SignaturePayload: Failed to create buffer!\n");
        exit(EXIT_FAILURE);
    }
    
    int patternLen = strlen(mask);
    unsigned long size = ModuleSize - TargetBaseAddress-0x601;
    
    for (unsigned long i = 0; i < size; i++) {
        ReadProcessMemory((void*)(TargetBaseAddress + i), buf, siglen * bsize);
        bool found = true;
        for (int j = 0; j < patternLen; j++) {
            if (mask[j] != '?' && signature[j] != *(char*)(buf+j)) {
                found = false;
                break;
            }
        }
        if (found) {
            addr = ((TargetBaseAddress+i)+sigoffset);
            Logger::log("SUCCESS", "SignaturePayload: Signature found -> " + int_to_hex(addr), LogType::PASSED);
            
            break;
        }
    }
    return addr;
}

// Function will write to target memory

bool ProcessManager::WriteProcessMemory(unsigned long address, void *buffer, uint size) {
  struct iovec local[1];
  struct iovec remote[1];

  local[0].iov_base = buffer;
  local[0].iov_len = size;
  remote[0].iov_base = (void *)address;
  remote[0].iov_len = size;

  return process_vm_writev(ProcessID, local, 1, remote, 1, 0) == size;
}

// Function will read from target memory

  bool ProcessManager::ReadProcessMemory(void* address, void *buffer, uint size) {
    struct iovec local[1];
    struct iovec remote[1];

    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = (void *)address;
    remote[0].iov_len = size;

    return process_vm_readv(ProcessID, local, 1, remote, 1, 0) == size;
}
ulong ProcessManager::FindDMAAddy(ulong ptr, std::vector<unsigned int> offsets) {
    ulong addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i) {
        ReadProcessMemory((void*)addr, &addr, sizeof(addr));
        addr += offsets[i];
    }
    return addr;
}

// Contructer will automatically attach itself to a process of choice

ProcessManager::ProcessManager(const char *szProcessName, const char *module) {
    // Check string length
    if(strlen(szProcessName) >= 1023) {
        fprintf(stderr, "[ERROR] ProcessManager: Process name is to long...\n");
        exit(EXIT_FAILURE);
    }

    // Copy string to private class buffer
    strcpy(ProcessNameString, szProcessName);

    // Create directory objects
    struct dirent   *DirectoryObject = NULL;
    DIR             *DirectoryHandle = NULL;
    // Open directory
    if((DirectoryHandle = opendir("/proc/")) == NULL) {
        fprintf(stderr, "[ERROR] ProcessManager: Failed to open PROC file system. Are you root?\n");
        exit(EXIT_FAILURE);
    }

    // Search for process
    while((DirectoryObject = readdir(DirectoryHandle)) != NULL) {
        // Check if directory is number(Process ID File)
        if(atoi(DirectoryObject->d_name) != 0) {
            char    FilePath[1024];
            char    *FileBuffer = NULL;
            __off_t FileLength  = 0;
            int     fd          = 0;

            sprintf(FilePath, "/proc/%s/status", DirectoryObject->d_name);  // Create new file path to read
            // Open status file
            if((fd = open(FilePath, O_RDONLY)) < 0) {
                fprintf(stderr, "[ERROR] ProcessManager: Failed to open PROC status file. Are you root?\n");
                exit(EXIT_FAILURE);
            }

            // Get file length
            FileLength = 128;

            // Create file buffer
            if((FileBuffer = (char *)malloc(FileLength)) == NULL) {
                fprintf(stderr, "[ERROR] ProcessManager: malloc()\n");
                exit(EXIT_FAILURE);
            }
            memset(FileBuffer, 0, FileLength);

            // Copy file to buffer
            if(read(fd, FileBuffer, FileLength - 1) < 0) {
                fprintf(stderr, "[ERROR] ProcessManager: Failed to read PROC status file. Are you root? : %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            // Close status file
            close(fd);

            // Check if process is correct
            if(strstr(FileBuffer, ProcessNameString) != NULL) {
                Logger::log("SUCCESS", "ProcessManager: Process " + std::string(ProcessNameString) + ":" + std::string(DirectoryObject->d_name) + " found!", LogType::PASSED);
                ProcessID = atol(DirectoryObject->d_name);

                // Unlock target memory
                //ptrace(PTRACE_ATTACH, ProcessID, NULL, NULL);

                // Create buffer to open target memory
                char TargetMemoryLocation[1024];
                sprintf(TargetMemoryLocation, "/proc/%s/mem", DirectoryObject->d_name);

                // Get the program base address
                TargetBaseAddress = FindBaseAddress(module);

                // Open target process memory
                if((ProcessHandle = open(TargetMemoryLocation, O_RDWR)) < 0) {
                    fprintf(stderr, "[ERROR] ProcessManager: Failed to ropen target process memory. Are you root? : %s\n", strerror(errno));
                    exit(EXIT_FAILURE);          
                }

                free(FileBuffer);
                break;
            }

            // Free file buffer
            free(FileBuffer);
        }
    }

    // Close directory
    closedir(DirectoryHandle);
}

// Deconstructor will close handle on target process

ProcessManager::~ProcessManager() {
    if(ProcessHandle != 0) {
        //ptrace(PTRACE_DETACH, ProcessID, NULL, NULL);
        close(ProcessHandle);
    }
}