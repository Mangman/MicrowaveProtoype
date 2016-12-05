//  Created by Stepan on 29.04.16.


#include <iostream>
#include <stdio.h>

#include <string.h>

#include "MyException.h"

#include "CPU.h"
int main()
{
    try
    {
        CPU<int, int, 5> cpu("output.tttt");
    }
    
    catch (my_exception& a)
    {
        printf("catch");
        printf("%s", a.what());
    }
    return 0;
}
