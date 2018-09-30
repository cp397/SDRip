#include "platform.h"
#include <stdio.h>
/******************************************************************************
 *
 *****************************************************************************/
int Platform::getDriveList(char** pszDriveList, int maxDrives) {

    char szDriveList[MAX_PATH] = {0};
    char* pszDrive = szDriveList;
    int numDrives = 0;   

    //Get the list of drives and copy them from one string into 
    //an array of strings: pszDriveList    
    GetLogicalDriveStrings(MAX_PATH, szDriveList);
    while(*pszDrive && numDrives < maxDrives) {
        strncpy(pszDriveList[numDrives++], pszDrive, 25);
        pszDrive += strlen(pszDrive) + 1;
    }
    
    return numDrives;
}

/******************************************************************************
 * Gets the drive type  
 ******************************************************************************/
char Platform::getDriveType(char* driveTypeSring, char* driveName){
	char driveType = GetDriveType(driveName);
	
	switch (driveType)
	{
		case 0:
			strncpy(driveTypeSring, "DRIVE_UNKNOWN", 13);	
		break;
			
		case 1:
			strncpy(driveTypeSring, "DRIVE_NO_ROOT_DIR", 17);
		break;		
		
		case 2:
			strncpy(driveTypeSring, "DRIVE_REMOVABLE", 15);
		break;
		
		case 3:
			strncpy(driveTypeSring, "DRIVE_FIXED", 11);
		break;
		
		case 4:
			strncpy(driveTypeSring, "DRIVE_REMOTE", 12);
		break;
		
		case 5:
			strncpy(driveTypeSring, "DRIVE_CDROM", 11);
		break;		
		
		case 6:
			strncpy(driveTypeSring, "DRIVE_RAMDISK", 13);
		break;														
	}
	return driveType;
}
