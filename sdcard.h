#ifndef SDRIP_H
#define SDRIP_H

#define SD_NUM_BLOCKS 3906250
#define SD_BLOCK_SIZE 512
#define SD_SUCCESS 0
#define SD_FAIL 1

class SDCard {

public:
    SDCard(char* device);        
    virtual ~SDCard();

    int readBlock(unsigned long blockNum, unsigned char* pBuffer);
    int writeBlock(unsigned long blockNum, unsigned char* pBuffer);
    
    //--- Inline functions ---//

    unsigned long getNumBlocks() {
        return SD_NUM_BLOCKS;
    }

    unsigned int getBlockSize() {
        return SD_BLOCK_SIZE;
    }

private:
    FILE* m_handle;
    char* m_device;
    unsigned char m_buffer[BUFSIZ];

    int openDevice();
    int closeDevice();
};

#endif
