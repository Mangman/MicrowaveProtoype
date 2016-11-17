//  Created by Stepan on 22/10/16.

#ifndef Assembler_h
#define Assembler_h

#include <string.h>
#include "MyException.h"

class Assembler {
private:
    //MARK: Members
    
    //TODO: даблы
    int* codes;
    FILE* file;
    long int fileSize;

public:
    //MARK: Constructors
    explicit Assembler (char* filePath);
    ~Assembler();
    
    Assembler( const Assembler& other ) {
        throw my_exception("you cant copy it.\n for the present", nullptr, PLACE);
    }
   
    Assembler( const Assembler&& other) {
        throw my_exception("you cant move it.\n for the present", nullptr, PLACE);
    }

    //MARK: Methods
    bool assemble ();
    int* getMachineCodes ();
};

Assembler::Assembler(char* filePath):
    codes(nullptr), file(nullptr), fileSize(-1) {
        file = fopen(filePath, "r");
        if (file == NULL) throw my_exception("Error with reading file", nullptr, PLACE);
        
        fseek(file , 0 , SEEK_END);
        fileSize = ftell(file);
        rewind (file);
        
        codes = new int [fileSize];
        if (codes == NULL) throw my_exception("Memory allocation error", nullptr, PLACE);
}

Assembler::~Assembler() {
    delete codes;
    fclose(file);
}

bool Assembler::assemble() {
    //Magic constant
    for (char* currentWord = new char[10] ; strcmp(currentWord, "end") != 0;) {
        fscanf(file, "%s", currentWord);
        printf ("%s %d\n", currentWord, strcmp(currentWord, "end"));
    }
    
    return true;
}


#endif /* Assembler_h_h */
