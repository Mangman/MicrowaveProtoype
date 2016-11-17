//  Created by Stepan on 17/11/16.

#ifndef Register_h
#define Register_h

#include "MyException.h"
#define PLACE place(__FILE__, __LINE__, __PRETTY_FUNCTION__)

template <typename valType>
class Register {
private:
    valType value;

public:
    
    explicit Register():
        value(NULL)
    {}
    
    void push(valType);
    
};

template <typename valType>
void Register<valType>::push(valType value) {
    if (value == NULL) throw my_exception("The register, you are trying to pop from, is empty.", nullptr, PLACE);
    else this->value = value;
}


#undef PLACE
#endif /* Register_h */
