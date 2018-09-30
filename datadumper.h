#ifndef HEX_DUMPER_H
#define HEX_DUMPER_H

/**
 * Holds 1 WiSARD packet of data elements
 **/
class Packet {
public:
	Packet(unsigned char* data);
	~Packet();

    unsigned char* pRawData;

    //Packet values
    

    //Data element values
    unsigned char deID;
    unsigned char deLen;
    unsigned char deVer;
    unsigned char procID;
    unsigned long timestamp;
    unsigned char tranID;
    unsigned char reportLen;
    unsigned char* data;
};

/**
 * Abstract base class for ouptut file dumper. The visit() method
 * must be implemented by each specific data dumper
 **/
class DataDumper {
public:
    virtual int dump(SDCard* sdcard, char* path);

private:
    virtual void visit(unsigned char * pBlock, FILE* fp) = 0;
};

/**
 * Output file visitor for ASCII HEX files
 **/
class HexDumper : public DataDumper {
private:
    static const unsigned char BYTES_PER_ROW = 8;
    void visit(unsigned char * pBlock, FILE* fp);
};

/**
 * Output file visitor for CSV files
 **/
class CSVDumper : public DataDumper {
private:
    void visit(unsigned char * pBlock, FILE* fp);
};

#endif
