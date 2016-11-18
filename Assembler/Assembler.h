//  Created by Stepan on 22/10/16.

#ifndef Assembler_h
#define Assembler_h

#include <string.h>

#include "MyException.h"
#include "CommandsEnum.h"

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
    
    FILE* output = fopen("output.tttt", "w");
    
    char* currentWord = new char[10];
    int* codes = new int [1];
    for (;;) {
        fscanf(file, "%s", currentWord);
        
        if (strcmp(currentWord, "push") == 0) {
            codes[0] = commands::CMD_PUSH;
            fwrite(codes, sizeof(char), 1, output);
            
            fscanf(file, "%s", currentWord);
            
            if (currentWord[1] == 'x') {
                codes[0] = 1;
                fwrite(codes, sizeof(char), 1, output);
                
                codes[0] = currentWord[0];
                fwrite(codes, sizeof(char), 1, output);
            }
            else {
                codes[0] = 0;
                fwrite(codes, sizeof(char), 1, output);
                //  Не понял зачем это
                char* end;
                codes[0] = int(strtol(currentWord, &end, 10));
                fwrite(codes, sizeof(int), 1, output);
                }
        }
        else if (strcmp(currentWord, "pop") == 0) {
            codes[0] = commands::CMD_POP;
            fwrite(codes, sizeof(char), 1, output);
            
            long currentPos = ftell(file);
            
            fscanf(file, "%s", currentWord);
            
            if (currentWord[1] == 'x') {
                codes[0] = 1;
                fwrite(codes, sizeof(char), 1, output);
                
                codes[0] = currentWord[0];
                fwrite(codes, sizeof(char), 1, output);
            }
            else {
                codes[0] = 0;
                fwrite(codes, sizeof(char), 1, output);

                fseek(file, currentPos, SEEK_SET);
            }
        }
        else if ((strcmp(currentWord, "jmp") == 0)) {
            codes[0] = commands::CMD_JMP;
            fwrite(codes, sizeof(char), 1, output);
            
            fscanf(file, "%s", currentWord);

            char* end;
            codes[0] = int(strtol(currentWord, &end, 10));
            fwrite(codes, sizeof(char), 1, output);
        }
        else if (currentWord[0] == ':') {
            codes[0] = commands::CMD_LBL;
            fwrite(codes, sizeof(char), 1, output);
            
            char* oldPtr = currentWord;
            currentWord = &(currentWord[1]);
            
            char* end;
            codes[0] = int(strtol(currentWord, &end, 10));
            fwrite(codes, sizeof(char), 1, output);
            
            currentWord = oldPtr;
        }
        //  Сделать дефайнами
        else if ((strcmp(currentWord, "add") == 0)) {
            codes[0] = commands::CMD_ADD;
            fwrite(codes, sizeof(char), 1, output);
        }
        else if ((strcmp(currentWord, "sub") == 0)) {
            codes[0] = commands::CMD_SUB;
            fwrite(codes, sizeof(char), 1, output);
        }
        else if ((strcmp(currentWord, "mul") == 0)) {
            codes[0] = commands::CMD_MUL;
            fwrite(codes, sizeof(char), 1, output);
        }
        else if ((strcmp(currentWord, "div") == 0)) {
            codes[0] = commands::CMD_DIV;
            fwrite(codes, sizeof(char), 1, output);
        }
        else if (strcmp(currentWord, "end")  == 0) {
            codes[0] = commands::CMD_END;
            fwrite(codes, sizeof(char), 1, output);
            break;
        }
        else {
            exit(228);
        }
    }
    
    fclose(output);
    return true;
}

#endif /* Assembler_h_h */
