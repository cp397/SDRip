#include "includes.h"

////Globals
static char pszFilePath[7];
static char pszDriveLabel[25];

/******************************************************************************
 * Struct for constructing menu options. Contains a text label, a flag to
 * enable or disable the menu option, and an action function pointer to
 * exectute if the menu option is selected (can be NULL for no action).
 *****************************************************************************/
typedef struct tagMenuOption {
    char *label;
    bool active;
    void (*action)(void);
} MenuOption;

static char ActionMenuLen = 3;

static MenuOption ActionMenu[] = {
    { (char*)"Rip Card     ", true, ripCard     },
    { (char*)"Erase Card   ", true, eraseCard   },
    { (char*)"Quit         ", true,  quit       }
};


/****************************************************************************
* Exit the application
*******************************************************************************/
void quit(){
	return;
}

///******************************************************************************
// * Select which drive is the SD card reader.  Enable the other menu options
// * after this is selected.
// *****************************************************************************/
void chooseDrive() {
    char* pszDriveList[20];
    char driveType[20];
	char* driveTypeString[20];
	char userInput[10];
    int nSelectedDrive;
    int numDrives;
    int driveIndex;
    
    // (first allocate array)
    for(int i=0; i<20; i++) {	
    	pszDriveList[i] = new char[25];
    	driveTypeString[i] = new char[25];
    	driveType[i] = -1;
	}
	
	//Get the list of system drives and drive types
	numDrives = Platform::getDriveList(pszDriveList, 20);
	
	printf("Drive Directory:\r\n");
	
    //Display drives
	for (int j = 0; j<numDrives;j++){
		driveType[j] = Platform::getDriveType(driveTypeString[j], strcat(pszDriveList[j],"\\"));
		printf("%d: %s ", j, pszDriveList[j]);
		printf("%s \r\n", driveTypeString[j]);
	}    
	// Prompt the user to select a valid drive (avoid the hard disk) 
	while(1){
	   	// Clear the input buffers
    	fflush(stdin);

		printf("Select a Drive:\r\n");	
		scanf ("%1d",&nSelectedDrive);

		if(driveType[nSelectedDrive] != DRIVE_REMOVABLE){
			printf("Invalid drive selected\r\n\n");
			continue;
		}
			
		printf("%s drive selected, correct?[y/n] \r\n", pszDriveList[nSelectedDrive]);		 
		scanf ("%2s",userInput);	
		
		if (strcmp("Y", userInput) == 0 || strcmp("y", userInput) == 0 ){

  			//Create the file path for the selected device
        	sprintf(pszFilePath, "\\\\.\\%s", pszDriveList[nSelectedDrive]);
        	pszFilePath[6] = '\0';
        	break;
    	}	
    
	}
	
    //Delete the dynamically allocated drive list
    for(int i=0; i<20; i++) delete pszDriveList[i];

}
/******************************************************************************
 * Asks user what they would like to do with the card 
/******************************************************************************/
void chooseAction()
{
	char userInput;
	
	printf("Select Action\r\n");
	
	for(int i = 0; i < ActionMenuLen; i++){
	printf("%d: %s\r\n",i, ActionMenu[i].label);
	}
	
	// Get selection from user
	scanf ("%1d",&userInput);
	
	// Print selection then vector to the handler
	printf( "%s\r\n", ActionMenu[userInput].label);
	ActionMenu[userInput].action();
	
}

/******************************************************************************
 * Export the data on the SD card to a file on one of this computer's drives
 *****************************************************************************/
void ripCard() {
    SDCard* sdcard;
    DataDumper* dumper;
	char FileName[50];
	
	printf("Ripping Card --- Warning this may take a while \n\r" );	
    
    // Allow user to enter a file name
	printf("Please Enter a File Name:\r\n");	
    scanf ("%40s",FileName);
    strcat(FileName, ".hex");//    strcat(FileName, ".csv");
    
    dumper = new HexDumper(); //CSVDumper();

    //Access the SD card drive
    sdcard = new SDCard(pszFilePath);

    printf("%s\r\n", FileName);
    //Dump the card using the selected Dumper
    dumper->dump(sdcard, FileName);
    
    // Delete the SD card object
    delete sdcard;
}

/******************************************************************************
 * Wipe all of the data from the SD cards (zero-out) - this isn't the same as
 * formatting since S.E.G.A. Wisards don't use filesystems on SD cards.
 *****************************************************************************/
void eraseCard() {
	 SDCard* sdcard;
     unsigned long numBlocks = sdcard->getNumBlocks();
     unsigned int blockSize  = sdcard->getBlockSize();
     unsigned char* pBuffer  = new unsigned char[blockSize];
     int j;
     
  	printf("Erasing Card --- Warning this may take a while \n\r" );	
    
	//Access the SD card drive
	sdcard = new SDCard(pszFilePath);

	// Clear the write buffer
	for(j = 0; j < blockSize; j++)
		{pBuffer[j] = 0;}
			   
     for(j= 0; j < numBlocks; j++){
		sdcard->writeBlock(j, pBuffer);
	 }

    // Delete the SD card object
    delete sdcard;
}

///******************************************************************************
// * Display a summary of the data on the SD card
// *****************************************************************************/
//void previewCard() {
//    //TODO: implement
//}
