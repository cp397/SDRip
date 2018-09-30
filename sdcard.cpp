#include "includes.h"

/******************************************************************************
 * Constructor -
 *****************************************************************************/
SDCard::SDCard(char* device): m_device(device), m_handle(NULL) {
    openDevice();
}

/******************************************************************************
 * Destructor - 
 *****************************************************************************/
SDCard::~SDCard() {
    closeDevice();
}

/******************************************************************************
 * Opens the device for reading in raw mode
 *****************************************************************************/
int SDCard::openDevice() {

    //Open device file in read/update raw mode
    m_handle = fopen(m_device, "rb+");
    
	if(m_handle == 0)
        printf("Error opening file: %s - %s\n", m_device, strerror(errno));
    
    //Set stream buffer
    setbuf(m_handle, (char*)m_buffer);
    return SD_SUCCESS;
}   

/******************************************************************************
 * Close the device file stream
 *****************************************************************************/
int SDCard::closeDevice() {
    int result = fclose(m_handle);
    m_handle = 0;
    
    if(result == SD_SUCCESS) return SD_SUCCESS;
    else return SD_FAIL;
}

/******************************************************************************
 * Read a block of bytes from the SD card
 *****************************************************************************/
int SDCard::readBlock(unsigned long blockNum, unsigned char* pBuffer) {

    //Attempt to seek to the desired block
    if(blockNum > 0) {
        int iRet = fseek(m_handle, blockNum*SD_BLOCK_SIZE, SEEK_SET);
        if(iRet != 0)
        { 
            printf("%s %d \n", strerror(errno), m_handle);
            return SD_FAIL;
        }
    }
 
    //Read the block into the buffer
    fread(pBuffer, 1, SD_BLOCK_SIZE, m_handle);
    fflush(m_handle);
    return SD_SUCCESS;
}

/******************************************************************************
 * Writes a block to the SD card
 *****************************************************************************/
int SDCard::writeBlock(unsigned long blockNum, unsigned char* pBuffer) {

    //Attempt to seek to the desired block
    if(blockNum > 0) {
        int iRet = fseek(m_handle, blockNum*SD_BLOCK_SIZE, SEEK_SET);
        if(iRet != 0)
        { 
            printf("%s %d \n", strerror(errno), m_handle);
            return SD_FAIL;
        }
    }
 
    //Write the block to the buffer
    fwrite(pBuffer, 1, SD_BLOCK_SIZE, m_handle);
    fflush(m_handle);
    return SD_SUCCESS;
}
