//  Created by Stepan on 17/11/16.

#ifndef CPU_h
#define CPU_h

#include "Stack.h"
#include "Register.h"
#include "MyException.h"
#include "CommandsEnum.h"
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

template <typename stackValType, typename registerType, int numberOfRegisters>
bool CPU<stackValType, registerType, numberOfRegisters>::execute() {
    for (int i = 0; codes[i] != CommandsEnum::CMD_END; i++) {
        switch (codes[i]) {
            case CommandsEnum::CMD_PUSH: {
                const char mode = codes[i+1];
                if (mode == 0) {
                    const char val = *((int*)&(codes[i+=2]));
                    cpu_stack.push(val);
                    
                    i += sizeof(int)/sizeof(char); // 4 вроде
                }
                else if (mode == 1) {
                    const char regNumber = codes[++i];
                    const registerType regValue = registers[regNumber].pop();
                    
                    cpu_stack.push(regValue);
                }
                break;
            }
            case CommandsEnum::CMD_POP: {
                
                break;
            }
            case CommandsEnum::CMD_ADD: {
                
                break;
            }
            case CommandsEnum::CMD_SUB: {
                
                break;
            }
            case CommandsEnum::CMD_MUL: {
                
                break;
            }
            case CommandsEnum::CMD_DIV: {
                
                break;
            }
            case CommandsEnum::CMD_JMP: {
                
                break;
            }
            case CommandsEnum::CMD_LBL: {
                
                break;
            }
            case CommandsEnum::CMD_END: {
                printf("execution ended.");
                break;
            }
            default: {
                throw my_exception("No command found.", NULL, PLACE);
                break;
            }
        }
    }
}

#endif /* CPU_h */
