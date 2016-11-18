//  Created by Stepan on 17/11/16.

#ifndef CPU_h
#define CPU_h

#include "Stack.h"
#include "Register.h"
#include "MyException.h"
//#include "FileReader.h"

template <typename stackValType, typename registerType, int numberOfRegisters>
class CPU {
private :
    Stack<stackValType> cpu_stack;
    char* codes;
    HeapArray<Register<registerType>> registers;
    
public :
    
    CPU (const char* inputFilePath);
    
    CPU( const CPU& other ) {
        throw my_exception("you cant copy it.\n for the present", nullptr, PLACE);
    }
    CPU( const CPU&& other) {
        throw my_exception("you cant move it.\n for the present", nullptr, PLACE);
    }
    
    bool execute();
};

template <typename stackValType, typename registerType, int numberOfRegisters>
CPU<stackValType, registerType, numberOfRegisters>::CPU(const char* inputFilePath):
    cpu_stack(Stack<stackValType>()), codes(nullptr), registers(HeapArray<Register<registerType>>(numberOfRegisters)) {
        //  Только чиселки
        for (int i = 0; i < numberOfRegisters; i++) {
            registers[i].push(0);
        }
        
        FILE* file = fopen(inputFilePath, "r");
        
        fseek(file , 0 , SEEK_END);
        long int fileSize = ftell(file);
        rewind (file);
        
        codes = new char [fileSize/sizeof(char)];
        
        fread(codes, sizeof(char), fileSize/sizeof(char), file);
}

#endif /* CPU_h */
