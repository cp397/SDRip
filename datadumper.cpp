#include "includes.h"

Packet::Packet(unsigned char* data) {

    pRawData = data;
}

Packet::~Packet() {

}

/******************************************************************************
 *
 *****************************************************************************/
int DataDumper::dump(SDCard* sdcard, char* path) {

    FILE* fp = fopen(path, "w");
    unsigned long numBlocks = sdcard->getNumBlocks();
    unsigned int blockSize  = sdcard->getBlockSize();
    unsigned char* pBuffer  = new unsigned char[blockSize];

    if(!fp)
	{
        return 1;   
    }
    
    //TODO: read format block from the card first (& display meta info?)

    //For each data block on the card....
    for(unsigned long i = 0; i < numBlocks; i++) {
		 
		printf("Blk Num=%d\r\n", i);
		//printf(".");	
        //Read the next block into a buffer and create a packet
        if(sdcard->readBlock(i, pBuffer) > 0) {
		    printf("Read Block Fail\r\n");	
			return 1;
        }	
	    //Dump the block
		this->visit(pBuffer, fp);
    }
    
    fclose(fp);
    return 0;
}

/******************************************************************************
 *
 *****************************************************************************/
void HexDumper::visit(unsigned char * pBlock, FILE* fp) {

	unsigned long ucLength;

	//For each byte in the current packet
    for(int i=0; i<SD_BLOCK_SIZE - 80; ) 
	{
        if (pBlock[i] == 0xFF && pBlock[i+1] == 0xF0 && pBlock[i+4] == 3  && pBlock[i+5] == 0x20){
		    for( int k = 0; k < SD_BLOCK_SIZE; ++k)
		        printf("%02X ", pBlock[k]);
		    ucLength = pBlock[i+10];
		   
		    if(ucLength > 80 || ucLength < 10){
		        continue;
		    }
    	    for (int j = 0; j < ucLength+4; j++){
			 	//Print the packet to the specified file
   		         fprintf(fp, "%02X ", pBlock[i+j]);
		    }
 		    fprintf(fp, "\n");
            fflush(fp);
 		    break;
 		   
		    i+=ucLength;	
        }
        else {
			 i++;
		}
    }
}

///******************************************************************************
// *
// *****************************************************************************/
//void CSVDumper::visit(Packet* packet, FILE* fp) {
//    
//    //Print out CSV column headers
//    fprintf(fp, "ProcessorID,Timestamp,TransducerID,Value\n");
//
//    //Parse out the data elements from the raw packet data
//    packet->deID  = packet->pRawData[0];
//    packet->deLen = packet->pRawData[1];
//    packet->deVer = packet->pRawData[2];
//    packet->procID    = packet->pRawData[3];
//    packet->timestamp = (unsigned long)(packet->pRawData[4]) << 3 | 
//                        (unsigned long)(packet->pRawData[5]) << 2 |
//                        (unsigned long)(packet->pRawData[6]) << 1 |
//                        (unsigned long)(packet->pRawData[7]);
//
//    //Parse out each (transducer, report length, data) triple
//    for(int i = 8; i < packet->deLen - 8; packet->deLen += packet->reportLen) {
//        packet->tranID    = packet->pRawData[i];
//        packet->reportLen = packet->pRawData[i+1];
//        packet->data      = packet->pRawData + i + 2;
//
//        //Print out each element in CSV format
//        fprintf(fp, "%u,%lu,%u,%lu", packet->procID, packet->timestamp, packet->tranID, (unsigned long)*(packet->data));
//    }
//}

/******************************************************************************
 *
 *****************************************************************************/
void CSVDumper::visit(unsigned char * pBlock, FILE* fp) {
    

    //Print out each element in CSV format
//	fprintf(fp, "%u,%lu,%u,%lu", packet->procID, packet->timestamp, packet->tranID, (unsigned long)*(packet->data));
    
}
