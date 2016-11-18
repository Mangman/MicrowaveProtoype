//  Created by Stepan on 22/10/16.

#include <iostream>

#include "Assembler.h"

int main() {
    try {
    char * filePath = "code.lal";
    
    Assembler asmm(filePath);
        
        asmm.assemble();
    }
    catch (my_exception& a)
    {
        printf("catch");
        printf("%s", a.what());
    }
    
    return 0;
}
