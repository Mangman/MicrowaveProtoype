//  Created by Stepan on 15/10/16.

#ifndef print_h
#define print_h

#include <string.h>

namespace  print {
    inline void print(signed int a)    {printf("%d",a);}
    inline void print(unsigned int a)  {printf("%u",a);}
    inline void print(float a)         {printf("%f", a);}
    inline void print(char a)          {printf("%c", a);}
    inline void print(char* a)         {printf("%s", a);}
    inline void print(std::string a)   {printf("%s", a.c_str());}
}
#endif /* print_h */
