//  Created by Stepan on 29.04.16.


#include <iostream>
#include <stdio.h>

#include <string.h>

#include "MyException.h"

#include "FileReader.h"

#include "CPU.h"
int main()
{
    try
    {
        Stack <int> a(12);
        a.dump();
        a.push (15);
        a.pop();
        
        a.dump();
        a.push(228);
        a.push(4);
        a.push(228);
        a.push(4);
        a.push(228);
        a.push(4);
        a.push(228);
        a.push(4);
        a.push(228);
        a.push(4);
        a.push(228);
        a.push(4);
        a.push(228);
        a.push(4);
        a.dump();
       
    }
    
    catch (my_exception& a)
    {
        printf("catch");
        printf("%s", a.what());
    }
    return 0;
}
