#ifndef PLATFORM_H
#define PLATFORM_H

#include <windows.h>

class Platform {
public:
    static int getDriveList(char** pszDriveList, int maxDrives);
    static char getDriveType(char* driveTypeSring, char* driveName);
};

#endif
