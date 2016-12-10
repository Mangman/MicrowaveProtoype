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
        printf ("started\n");
        CPU<int, 5> cpu("output.tttt");
        cpu.execute();
    }
    
    catch (my_exception& a)
    {
        printf("catch");
        printf("%s", a.what());
    }
    return 0;
}
