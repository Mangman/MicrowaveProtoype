//  Created by Stepan on 17/11/16.

#ifndef Register_h
#define Register_h

#include "MyException.h"

template <typename valType>
class Register {
private:
    valType value;

public:
    
    explicit Register():
        value(NULL)
    {}
    
    void push(valType);
    
    valType pop();
    
};

template <typename valType>
void Register<valType>::push(valType value) {
    this->value = value;
}

template <typename valType>
valType Register<valType>::pop() {
    if (value == NULL) throw my_exception("The register, you are trying to pop from, is empty.", nullptr, PLACE);
    else {
        return value;
    }
}

#endif /* Register_h */
