//  Created by Stepan on 22/10/16.

#ifndef FileInterface_h
#define FileInterface_h

#include "myException.h"

template <typename dataType>
class FileReader {
    
private:
    dataType* data;
    long int fileSize;
    FILE* file;
    bool gaveData = false;
    
public:
    explicit FileReader (char* filePath):
    data(nullptr), file(nullptr) {
        file = fopen(filePath, "r");
        if (file == NULL) throw my_exception("Error with reading file", nullptr, PLACE);
    }
    
    ~FileReader () {
        fclose(file);
        //Weird solution
        if (gaveData == false) delete data;
    }
    
    bool loadFile();
    
    inline dataType* getData ();
    inline long int getSize () {return fileSize;}
};

template <typename dataType>
bool FileReader<dataType>::loadFile() {
    fseek(file , 0 , SEEK_END);
    long int fileSize = ftell(file);
    rewind (file);
    
    data = new dataType(sizeof(dataType)*fileSize);
    if (data == NULL) throw my_exception("Memory allocation error", nullptr, PLACE);

    size_t result = fread(data, sizeof(dataType), fileSize, file);
    if (result != fileSize) throw my_exception("Reading file error", nullptr, PLACE);
}

template <typename dataType>
inline dataType* FileReader<dataType>::getData () {
    gaveData = true;
    return data;
}

#endif /* FileInterface_h */
