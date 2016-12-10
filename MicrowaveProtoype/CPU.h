//  Created by Stepan on 17/11/16.

#ifndef CPU_h
#define CPU_h

#include "Stack.h"
#include "Register.h"
#include "MyException.h"
#include "CommandsEnum.h"
//#include "FileReader.h"

template <typename stackValType, int numberOfRegisters>
class CPU {
private :
    Stack<stackValType> cpu_stack;
    char* codes;
    long codes_len;
    HeapArray<Register<stackValType>> registers;
    
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

template <typename stackValType, int numberOfRegisters>
CPU<stackValType, numberOfRegisters>::CPU(const char* inputFilePath):
    cpu_stack(Stack<stackValType>()), codes(nullptr), registers(HeapArray<Register<stackValType>>(numberOfRegisters)) {
        //  Только чиселки
        for (int i = 0; i < numberOfRegisters; i++) {
            registers[i].push(0);
        }
        
        FILE* file = fopen(inputFilePath, "r");
        
        fseek(file , 0 , SEEK_END);
        long int fileSize = ftell(file);
        rewind (file);
        
        codes_len = fileSize/sizeof(char);
        codes = new char [codes_len];
        
        fread(codes, sizeof(char), codes_len, file);
}

template <typename stackValType, int numberOfRegisters>
bool CPU<stackValType, numberOfRegisters>::execute() {
    for (int i = 0; codes[i] != CommandsEnum::CMD_END; i++) {
        switch (codes[i]) {
            case CommandsEnum::CMD_PUSH: {
                const char mode = codes[++i];
                if (mode == 0) {
                    const char val =  *(int*) &codes[++i];
                    cpu_stack.push(val);
                    
                    i += sizeof(int)/sizeof(char);
                    i--; // компенсация
                }
                else if (mode == 1) {
                    const char regNumber = codes[++i];
                    if (regNumber > numberOfRegisters) {
                        throw my_exception("No such register found", NULL, PLACE);
                    }
                    const stackValType regValue = registers[regNumber].pop();
                    
                    cpu_stack.push(regValue);
                }
                else {
                    throw my_exception("No such push mode found.", NULL, PLACE);
                }
                break;
            }
            case CommandsEnum::CMD_POP: {
                const char mode = codes[++i];
                if (mode == 0) {
                    // skipping 0 value
                    i += 1;
                }
                else if (mode == 1) {
                    const char regNumber = codes[++i];
                    
                    if (regNumber > numberOfRegisters) {
                        throw my_exception("No such register found", NULL, PLACE);
                    }
                    
                    stackValType val = cpu_stack.pop();
                    registers[regNumber].push(val);
                    
                }
                else {
                    throw my_exception("No such pop mode found.", NULL, PLACE);
                }

                break;
            }
            case CommandsEnum::CMD_ADD: {
                //Спросить Илью Рудольфовича про оператор
                cpu_stack.push(cpu_stack.pop()+cpu_stack.pop());
                break;
            }
            case CommandsEnum::CMD_SUB: {
                cpu_stack.push(cpu_stack.pop()-cpu_stack.pop());
                break;
            }
            case CommandsEnum::CMD_MUL: {
                cpu_stack.push(cpu_stack.pop()*cpu_stack.pop());
                break;
            }
            case CommandsEnum::CMD_DIV: {
                cpu_stack.push(cpu_stack.pop()/cpu_stack.pop());
                break;
            }
            case CommandsEnum::CMD_JMP: {
                char adress = codes[++i];
                if (i > codes_len) {
                    throw my_exception("Jmp adress out of range.", NULL, PLACE);
                }
                printf ("Jumped to %d\n", adress);
                i = adress-1;
                break;
            }
            case CommandsEnum::CMD_END: {
                printf("execution ended.");
                return true;
                break;
            }
            default: {
                printf ("ldldl\n");
                throw my_exception("No command found.", NULL, PLACE);
                break;
            }
        }
    }
    return true;
}

#endif /* CPU_h */
