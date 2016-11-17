//  Created by Stepan on 17/11/16.

#ifndef CPU_h
#define CPU_h

#include "Stack.h"
#include "Register.h"
#include "MyException.h"

#define PLACE place(__FILE__, __LINE__, __PRETTY_FUNCTION__)


template <class stackValType, class registerType>
class CPU {
private :
    Stack<stackValType> cpu_stack;
    HeapArray<int> codes;
    HeapArray<Register<registerType>> registers;
    
public :
    
    CPU ();
    
    CPU( const CPU& other ) {
        throw my_exception("you cant copy it.\n for the present", nullptr, PLACE);
    }
    CPU( const CPU&& other) {
        throw my_exception("you cant move it.\n for the present", nullptr, PLACE);
    }
    
};


#undef PLACE

#endif /* CPU_h */
